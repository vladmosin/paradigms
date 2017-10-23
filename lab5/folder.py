import yat.model as m
import printer as printer


class ConstantFolder:
    def __init__(self):
        self.scope = m.Scope()

    def visit(self, tree):
        return tree.accept(self)

    def visitNumber(self, number):
        return number

    def visitReference(self, reference):
        return reference

    def visitUnaryOperation(self, unary_operation):
        expr = unary_operation.expr.accept(self)
        if type(expr) == m.Number:
            return unary_operation.evaluate(self.scope)
        return unary_operation

    def visitBinaryOperation(self, binary_operation):
        lhs = binary_operation.lhs.accept(self)
        rhs = binary_operation.rhs.accept(self)
        if type(lhs) == m.Number and type(rhs) == m.Number:
            return m.BinaryOperation(lhs, binary_operation.op,
                                     rhs).evaluate(self.scope)
        if type(rhs) == m.Number and\
           type(lhs) == m.Reference and\
           binary_operation.op == "*":
            if rhs.value == 0:
                binary_operation.lhs = m.Number(0)
                return m.Number(0)
        if type(lhs) == m.Number and\
           type(rhs) == m.Reference and\
           binary_operation.op == "*":
            if lhs.value == 0:
                binary_operation.rhs = m.Number(0)
                return m.Number(0)
        if type(lhs) == m.Reference and\
           type(rhs) == m.Reference and\
           binary_operation.op == '-':
            if lhs.name == rhs.name:
                binary_operation.lhs = m.Number(0)
                binary_operation.rhs = m.Number(0)
                return m.Number(0)
        return m.BinaryOperation(lhs, binary_operation.op, rhs)

    def visitFunctionDefinition(self, func_def):
        body = []
        for statement in func_def.function.body or []:
            body.append(statement.accept(self))
        func_def.function.body = body
        return m.FunctionDefinition(func_def.name, func_def.function)

    def visitConditional(self, conditional):
        true_list = []
        false_list = []
        for true_statement in conditional.if_true or []:
            true_list.append(true_statement.accept(self))
        for false_statement in conditional.if_false or []:
            false_list.append(false_statement.accept(self))
        return m.Conditional(conditional.condition.accept(self),
                             true_list, false_list)

    def visitFunctionCall(self, func_call):
        list_of_args = []
        for arg in func_call.args or []:
            list_of_args.append(arg.accept(self))
        return m.FunctionCall(func_call.fun_expr.accept(self), list_of_args)

    def visitPrint(self, print_expr):
        return m.Print(print_expr.expr.accept(self))

    def visitRead(self, read_expr):
        return m.Read(read_expr.name)


def main():
    v = ConstantFolder()
    p = printer.PrettyPrinter()

if __name__ == "__main__":
    main()

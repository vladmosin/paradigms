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
            return binary_operation.evaluate(self.scope)
        if type(binary_operation.rhs) == m.Number and\
           type(binary_operation.lhs) == m.Reference and\
           binary_operation.op == "*":
            if binary_operation.rhs.value == 0:
                binary_operation.rhs = m.Number(0)
                return m.Number(0)
        if type(binary_operation.lhs) == m.Number and\
           type(binary_operation.rhs) == m.Reference and\
           binary_operation.op == "*":
            if binary_operation.rhs.value == 0:
                binary_operation.rhs = m.Number(0)
                return m.Number(0)
        if type(binary_operation.lhs) == m.Reference and\
           type(binary_operation.rhs) == m.Reference and\
           binary_operation.op == "-":
            if binary_operation.lhs.name == binary_operation.rhs.name:
                binary_operation.lhs = m.Number(0)
                binary_operation.rhs = m.Number(0)
                return m.Number(0)
        return binary_operation

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
    p.visit(v.visit(m.Print(m.Number(10))))
    p.visit(v.visit(m.UnaryOperation('-', m.Number(10))))
    p.visit(v.visit(m.BinaryOperation(m.BinaryOperation(
                              m.Reference('foo'), '+',
                              m.Number(7)), '*', m.Number(2))))
    p.visit(v.visit(m.Read("read")))
    p.visit(v.visit(m.Conditional(m.Number(5), [
                    m.BinaryOperation(m.Reference('var'), '-',
                                      m.Number(-5))])))
    p.visit(v.visit(m.FunctionDefinition('summer', m.Function(['a', 'b'], [
            m.Print(m.BinaryOperation(m.Reference('a'), '+',
                                      m.Reference('b'))),
            m.BinaryOperation(m.Reference('a'), '+', m.Reference('b'))]))))
    p.visit(v.visit(m.FunctionCall(m.Reference('summer'), [
                    m.Number(1),
                    m.BinaryOperation(m.Number(2), '+', m.Number(3))])))
    p.visit(v.visit(m.Print(m.Conditional(m.BinaryOperation(
          m.Number(4), '-', m.Number(4)), [], [
          m.BinaryOperation(m.Number(9), '/', m.Number(3)), m.Reference('var')
          ]))))
    p.visit(v.visit(m.FunctionDefinition('abs', m.Function(['a', 'b'], [
        m.Conditional(m.BinaryOperation(
                      m.BinaryOperation(m.Reference('a'), '-',
                                        m.Reference('b')), '>', m.Number(0)), [
                    m.Print(m.BinaryOperation(m.Reference('a'), '-',
                                              m.Reference('b')))
                    ], [
            m.Print(m.BinaryOperation(m.Reference('b'), '-', m.Reference('a')))
        ])
    ]))))
    p.visit(v.visit(m.FunctionCall(m.Reference('abs'), [
        m.Number(23),
        m.UnaryOperation('-', m.Number(-30))
    ])))
    p.visit(v.visit(m.FunctionDefinition('fu', m.Function([], []))))
    p.visit(v.visit(m.FunctionCall(m.Reference('fu'), [])))

if __name__ == "__main__":
    main()

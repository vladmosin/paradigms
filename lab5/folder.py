import yat.model as m


class ConstantFolder:
    def __init__(self):
        self.oper = 0
        self.scope = m.Scope()

    def visit(self, tree):
        self.oper = 0
        return "{}".format(tree.accept(self))

    def visitNumber(self, number):
        return "Number({})".format(number.value)

    def visitReference(self, reference):
        self.oper = 1
        return "Reference(\'{}\')".format(reference.name)

    def visitUnaryOperation(self, unary_operation):
        current_oper = self.oper
        self.oper = 0
        string_to_return = "UnaryOperation(\'{}\', {})".format(
                unary_operation.op, unary_operation.expr.accept(self))
        if self.oper == 0:
            return "Number({})".format(
                unary_operation.evaluate(self.scope).value)
        return string_to_return

    def visitBinaryOperation(self, binary_operation):
        current_oper = self.oper
        self.oper = 0
        count_lhs = 0
        count_rhs = 0
        str_lhs = "{}".format(binary_operation.lhs.accept(self))
        count_lhs = self.oper
        self.oper = 0
        str_rhs = "{}".format(binary_operation.rhs.accept(self))
        count_rhs = self.oper
        self.oper = max(count_lhs, count_rhs)
        if self.oper == 0:
            return "Number({})".format(
                binary_operation.evaluate(self.scope).value)
        else:
            if count_rhs == 0:
                if binary_operation.rhs.evaluate(self.scope).value == 0 and\
                   type(binary_operation.lhs) == m.Reference and\
                   binary_operation.op == "*":
                    self.oper = 0
                    binary_operation.lhs = m.Number(0)
                    return "Number(0)"
            if count_lhs == 0:
                if binary_operation.lhs.evaluate(self.scope).value == 0 and\
                   type(binary_operation.rhs) == m.Reference and\
                   binary_operation.op == "*":
                    self.oper = 0
                    binary_operation.rhs = m.Number(0)
                    return "Number(0)"
            if type(binary_operation.lhs) == m.Reference and\
               type(binary_operation.rhs) == m.Reference and\
               binary_operation.op == "-":
                if binary_operation.lhs.name == binary_operation.rhs.name:
                    self.oper = 0
                    binary_operation.lhs = m.Number(0)
                    binary_operation.rhs = m.Number(0)
                    return "Number(0)"
        return "BinaryOperation({}, \'{}\', {})".format(
                str_lhs, binary_operation.op, str_rhs)

    def visitFunctionDefinition(self, func_def):
        body = ""
        for statement in func_def.function.body or []:
            if len(body) == 0:
                body += statement.accept(self)
            else:
                body += ", {}".format(statement.accept(self))
        return "FunctionDefinition(\'{}\', Function({}, [{}])".format(
                    func_def.name, func_def.function.args, body)

    def visitConditional(self, conditional):
        true_string = ""
        false_string = ""
        for true_statement in conditional.if_true or []:
            if len(true_string) == 0:
                true_string += true_statement.accept(self)
            else:
                true_string += ", {}".format(true_statement.accept(self))
        for false_statement in conditional.if_false or []:
            if len(false_string) == 0:
                false_string += false_statement.accept(self)
            else:
                false_string += ", {}".format(false_statement.accept(self))
        return "Conditional({}, [{}], [{}])".format(
                conditional.condition.accept(self), true_string, false_string)

    def visitFunctionCall(self, func_call):
        self.oper = 1
        string_of_args = ""
        for arg in func_call.args or []:
            if len(string_of_args) == 0:
                string_of_args += arg.accept(self)
            else:
                string_of_args += ", " + arg.accept(self)
        return "FunctionCall({}, [{}])".format(
                func_call.fun_expr.accept(self), string_of_args)

    def visitPrint(self, print_expr):
        return "Print({})".format(print_expr.expr.accept(self))

    def visitRead(self, read_expr):
        return "Read(\'{}\')".format(read_expr.name)


def main():
    v = ConstantFolder()
    print(v.visit(m.Print(m.Number(10))))
    print(v.visit(m.UnaryOperation('-', m.Number(10))))
    print(v.visit(m.BinaryOperation(m.BinaryOperation(
                              m.Reference('foo'), '+',
                              m.Number(7)), '*', m.Number(2))))
    print(v.visit(m.Read("read")))
    print(v.visit(m.Conditional(m.Number(5), [
                             m.BinaryOperation(m.Reference('var'), '-',
                                m.Number(-5))
                             ])))
    print(v.visit(m.FunctionDefinition('summer', m.Function(['a', 'b'], [
            m.Print(m.BinaryOperation(m.Reference('a'), '+',
                                      m.Reference('b'))),
            m.BinaryOperation(m.Reference('a'), '+', m.Reference('b'))
    ]))))
    print(v.visit(m.FunctionCall(m.Reference('summer'), [
        m.Number(1),
        m.BinaryOperation(m.Number(2), '+', m.Number(3))
    ])))
    print(v.visit(m.Print(m.Conditional(m.BinaryOperation(
          m.Number(4), '-', m.Number(4)), [], [
          m.BinaryOperation(m.Number(9), '/', m.Number(3)), m.Reference('var')
          ]))))
    print(v.visit(m.FunctionDefinition('abs', m.Function(['a', 'b'], [
        m.Conditional(m.BinaryOperation(
                      m.BinaryOperation(m.Reference('a'), '-',
                                        m.Reference('b')), '>', m.Number(0)), [
                    m.Print(m.BinaryOperation(m.Reference('a'), '-',
                                              m.Reference('b')))
                    ], [
            m.Print(m.BinaryOperation(m.Reference('b'), '-', m.Reference('a')))
        ])
    ]))))
    print(v.visit(m.FunctionCall(m.Reference('abs'), [
        m.Number(23),
        m.UnaryOperation('-', m.Number(-30))
    ])))
    print(v.visit(m.FunctionDefinition('fu', m.Function([], []))))
    print(v.visit(m.FunctionCall(m.Reference('fu'), [])))
    print(v.visit(m.Print(m.BinaryOperation(m.Number(5), '&&', m.Number(6)))))
    print(v.visit(m.Print(m.BinaryOperation(m.Number(3), '<', m.Number(5)))))
    print(v.visit(m.Print(m.Conditional(m.Number(3), None, None))))
    print(v.visit(m.Print(m.BinaryOperation(m.Number(1), '||', m.Number(4)))))

if __name__ == "__main__":
    main()

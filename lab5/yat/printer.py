import yat.model as m


class PrettyPrinter:
    def __init__(self):
        self.spaces = 0

    def visit(self, tree):
        print("{};".format(tree.accept(self)))

    def visitNumber(self, number):
        return str(number.value)

    def visitReference(self, reference):
        return reference.name

    def visitUnaryOperation(self, unary_operation):
        return "{}({})".format(unary_operation.op,
                               unary_operation.expr.accept(self))

    def visitBinaryOperation(self, binary_operation):
        return "({} {} {})".format(binary_operation.lhs.accept(self),
                                   binary_operation.op,
                                   binary_operation.rhs.accept(self))

    def visitFunctionDefinition(self, func_def):
        args = ""
        for arg in func_def.function.args:
            if args == "":
                args += arg
            else:
                args += ", " + arg
        string_to_return = "def {}({}) {}\n".format(func_def.name, args, "{")
        self.spaces += 4
        for statement in func_def.function.body or []:
            string_to_return += "{}{};\n".format(" " * self.spaces,
                                                 statement.accept(self))
        self.spaces -= 4
        string_to_return += "{}{}".format(" " * self.spaces, '}')
        return string_to_return

    def visitConditional(self, conditional):
        string_to_return = "if ({}) {}\n".format(
            conditional.condition.accept(self), '{')
        self.spaces += 4
        for true_statement in conditional.if_true or []:
            string_to_return += "{}{};\n".format(" " * self.spaces,
                                                 true_statement.accept(self))
        string_to_return += "{}{} else {}\n".format(
                    " " * (self.spaces - 4), '}', '{')
        for false_statement in conditional.if_false or []:
            string_to_return += "{}{};\n".format(" " * self.spaces,
                                                 false_statement.accept(self))
        self.spaces -= 4
        string_to_return += "{}{}".format(" " * self.spaces, '}')
        return string_to_return

    def visitFunctionCall(self, func_call):
        string_of_args = ""
        for arg in func_call.args or []:
            if len(string_of_args) == 0:
                string_of_args += arg.accept(self)
            else:
                string_of_args += ", " + arg.accept(self)
        return "{}({})".format(func_call.fun_expr.accept(self), string_of_args)

    def visitPrint(self, print_expr):
        return "print {}".format(print_expr.expr.accept(self))

    def visitRead(self, read_expr):
        return "read {}".format(read_expr.name)


def main():
    v = PrettyPrinter()
    v.visit(m.Print(m.Number(10)))
    v.visit(m.UnaryOperation('-', m.Number(10)))
    v.visit(m.BinaryOperation(m.BinaryOperation(
                              m.Reference('foo'), '+',
                              m.Number(7)), '*', m.Number(2)))
    v.visit(m.Read("read"))
    v.visit(m.Conditional(m.Number(5), [
                             m.BinaryOperation(m.Reference('var'), '-',
                                               m.Number(-5))
                             ]))
    v.visit(m.FunctionDefinition('summer', m.Function(['a', 'b'], [
            m.Print(m.BinaryOperation(m.Reference('a'), '+',
                                      m.Reference('b'))),
            m.BinaryOperation(m.Reference('a'), '+', m.Reference('b'))])))
    v.visit(m.FunctionCall(m.Reference('summer'), [
        m.Number(1),
        m.BinaryOperation(m.Number(2), '+', m.Number(3))
    ]))
    v.visit(m.Print(m.Conditional(m.BinaryOperation(
          m.Number(4), '-', m.Number(4)), [], [
          m.BinaryOperation(m.Number(9), '/', m.Number(3)), m.Reference('var')
          ])))
    v.visit(m.FunctionDefinition('abs', m.Function(['a', 'b'], [
        m.Conditional(m.BinaryOperation(m.BinaryOperation(m.Reference('a'),
                      '-', m.Reference('b')), '>', m.Number(0)), [
                    m.Print(m.BinaryOperation(m.Reference('a'), '-',
                                              m.Reference('b')))
                    ], [
            m.Print(m.BinaryOperation(m.Reference('b'), '-', m.Reference('a')))
        ])
    ])))
    v.visit(m.FunctionCall(m.Reference('abs'), [
        m.Number(23),
        m.UnaryOperation('-', m.Number(-30))
    ]))
    v.visit(m.FunctionDefinition('fu', m.Function([], [])))
    v.visit(m.FunctionCall(m.Reference('fu'), []))
    v.visit(m.Print(m.BinaryOperation(m.Number(5), '&&', m.Number(6))))
    v.visit(m.Print(m.BinaryOperation(m.Number(3), '<', m.Number(5))))
    v.visit(m.Print(m.Conditional(m.Number(3), None, None)))
    v.visit(m.Print(m.BinaryOperation(m.Number(1), '||', m.Number(4))))


if __name__ == "__main__":
    main()

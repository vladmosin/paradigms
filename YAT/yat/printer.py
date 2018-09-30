import yat.model as m


class PrettyPrinter:
    def __init__(self):
        self.spaces = 0

    def visit(self, tree):
        print("{};".format(tree.accept(self)))

    def visit_number(self, number):
        return str(number.value)

    def visit_reference(self, reference):
        return reference.name

    def visit_unary_operation(self, unary_operation):
        return "{}({})".format(unary_operation.op,
                               unary_operation.expr.accept(self))

    def visit_binary_operation(self, binary_operation):
        return "({} {} {})".format(binary_operation.lhs.accept(self),
                                   binary_operation.op,
                                   binary_operation.rhs.accept(self))

    def visit_function_definition(self, func_def):
        return "def {}({}) {{\n{}{}}}".format(
            func_def.name,
            ", ".join(arg for arg in func_def.function.args or []),
            self.format_list(func_def.function.body),
            self.return_spaces())

    def visit_conditional(self, conditional):
        return "if ({}) {{\n{}{}}} else {{\n{}{}}}".format(
            conditional.condition.accept(self),
            self.format_list(conditional.if_true),
            self.return_spaces(),
            self.format_list(conditional.if_false),
            self.return_spaces())

    def visit_function_call(self, func_call):
        return "{}({})".format(
            func_call.fun_expr.accept(self),
            ", ".join(arg.accept(self) for arg in func_call.args or []))

    def visit_print(self, print_expr):
        return "print {}".format(print_expr.expr.accept(self))

    def visit_read(self, read_expr):
        return "read {}".format(read_expr.name)

    def format_list(self, expr_list):
        self.spaces += 4
        result = "".join("{}{};\n".format(
            self.return_spaces(),
            expr.accept(self)) for expr in expr_list or [])
        self.spaces -= 4
        return result

    def return_spaces(self):
        return " " * self.spaces


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


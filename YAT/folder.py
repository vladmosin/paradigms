import yat.model as m
import yat.printer as printer


class ConstantFolder:
    def __init__(self):
        self.scope = m.Scope()

    def visit(self, tree):
        return tree.accept(self)

    def visit_number(self, number):
        return number

    def visit_reference(self, reference):
        return reference

    def visit_unary_operation(self, unary_operation):
        expr = unary_operation.expr.accept(self)
        if type(expr) == m.Number:
            return m.UnaryOperation(unary_operation.op,
                                    expr).evaluate(self.scope)
        return m.UnaryOperation(unary_operation.op, expr)

    def visit_binary_operation(self, binary_operation):
        lhs = binary_operation.lhs.accept(self)
        rhs = binary_operation.rhs.accept(self)
        if type(lhs) == m.Number and type(rhs) == m.Number:
            return m.BinaryOperation(lhs, binary_operation.op,
                                     rhs).evaluate(self.scope)
        if (type(rhs) == m.Number and rhs.value == 0 and
           type(lhs) == m.Reference and
           binary_operation.op == "*"):
            return m.Number(0)
        if (type(lhs) == m.Number and lhs.value == 0 and
           type(rhs) == m.Reference and
           binary_operation.op == "*"):
            return m.Number(0)
        if (type(lhs) == m.Reference and
           type(rhs) == m.Reference and lhs.name == rhs.name and
           binary_operation.op == '-'):
            return m.Number(0)
        return m.BinaryOperation(lhs, binary_operation.op, rhs)

    def visit_function_definition(self, func_def):
        return m.FunctionDefinition(
               func_def.name,
               m.Function(func_def.function.args,
                          self.optimize_list(func_def.function.body)))

    def visit_conditional(self, conditional):
        return m.Conditional(conditional.condition.accept(self),
                             self.optimize_list(conditional.if_true),
                             self.optimize_list(conditional.if_false))

    def visit_function_call(self, func_call):
        return m.FunctionCall(func_call.fun_expr.accept(self),
                              self.optimize_list(func_call.args))

    def visit_print(self, print_expr):
        return m.Print(print_expr.expr.accept(self))

    def visit_read(self, read_expr):
        return m.Read(read_expr.name)

    def optimize_list(self, expr_list):
        return [expr.accept(self)
                for expr in expr_list or []]


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
    p.visit(v.visit(m.BinaryOperation(m.Reference('g'),
                    '-', m.Reference('a'))))

if __name__ == "__main__":
    main()


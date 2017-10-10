class Number:
    def __init__(self, value):
        self.value = value

    def evaluate(self, scope):
        return self

    def __hash__(self):
        return hash(self.value)

    def __eq__(self, other):
        return self.value == other.value


class Scope:
    def __init__(self, parent=None):
        self.parent = parent
        self.values = {}

    def __getitem__(self, key):
        if key in self.values:
            return self.values[key]
        elif self.parent:
            return self.parent[key]

    def __setitem__(self, key, value):
        self.values[key] = value


class Function:
    def __init__(self, args, body):
        self.args = args
        self.body = body

    def evaluate(self, scope):
        return self


class FunctionDefinition:
    def __init__(self, name, function):
        self.name = name
        self.function = function

    def evaluate(self, scope):
        scope[self.name] = self.function
        return self.function


class Conditional:
    def __init__(self, condition, if_true, if_false=None):
        self.condition = condition
        self.if_true = if_true
        self.if_false = if_false

    def evaluate(self, scope):
        if self.condition.evaluate(scope).value == 0:
            return result(self.if_false, scope)
        else:
            return result(self.if_true, scope)


class Print:
    def __init__(self, expr):
        self.expr = expr

    def evaluate(self, scope):
        num = self.expr.evaluate(scope)
        print(num.value)
        return num


class Read:
    def __init__(self, name):
        self.name = name

    def evaluate(self, scope):
        value = int(input())
        scope[self.name] = Number(value)
        return Number(value)


class FunctionCall:
    def __init__(self, fun_expr, args):
        self.fun_expr = fun_expr
        self.args = args

    def evaluate(self, scope):
        function = self.fun_expr.evaluate(scope)
        call_scope = Scope(scope)
        for arg, value in zip(function.args, self.args):
            call_scope[arg] = value.evaluate(scope)
        return result(function.body, call_scope)


class Reference:
    def __init__(self, name):
        self.name = name

    def evaluate(self, scope):
        return scope[self.name]


class BinaryOperation:
    def __init__(self, lhs, op, rhs):
        self.rhs = rhs
        self.op = op
        self.lhs = lhs

    def evaluate(self, scope):
        left = self.lhs.evaluate(scope).value
        right = self.rhs.evaluate(scope).value
        d = {'+': left + right,
             '-': left - right,
             '*': left * right,
             '/': left // right if right != 0 else 0,
             '%': left % right if right != 0 else 0,
             '==': 1 if left == right else 0,
             '!=': 1 if left != right else 0,
             '<': 1 if left < right else 0,
             '>': 1 if left > right else 0,
             '<=': 1 if left <= right else 0,
             '>=': 1 if left >= right else 0,
             '&&': 0 if right == 0 and left == 0 else 1,
             '||': 0 if right == 0 or left == 0 else 1}
        return Number(d[self.op])


class UnaryOperation:
    def __init__(self, op, expr):
        self.op = op
        self.expr = expr

    def evaluate(self, scope):
        expression = self.expr.evaluate(scope).value
        d = {'-': 0 - expression,
             '!': 0 if expression == 0 else 1}
        return Number(d[self.op])


def result(expr, scope):
        res = Number(0)
        for statement in expr:
            res = statement.evaluate(scope)
        return res


def main():
    parent = Scope()
    Print(Number(10)).evaluate(parent)
    Print(UnaryOperation('-', Number(10))).evaluate(parent)
    parent['foo'] = Number(10)
    program = BinaryOperation(BinaryOperation(
                              Reference('foo'), '+',
                              Number(7)), '*', Number(2))
    result = program.evaluate(parent)
    Print(result).evaluate(parent)
    scope = Scope(parent)
    Print(parent['foo']).evaluate(scope)
    value = Read("read").evaluate(scope)
    scope['var'] = Number(8)
    Print(value).evaluate(parent)
    cond_check = Conditional(Number(5), [
                             BinaryOperation(Reference('var'), '-',
                                             Number(-5))
                             ])
    cond_check_result = cond_check.evaluate(scope)
    Print(cond_check_result).evaluate(scope)
    operation1 = FunctionDefinition('summer', Function(['a', 'b'], [
            Print(BinaryOperation(Reference('a'), '+', Reference('b'))),
            BinaryOperation(Reference('a'), '+', Reference('b'))
    ]))
    operation2 = FunctionCall(Reference('summer'), [
        Number(1),
        BinaryOperation(Number(2), '+', Number(3))
    ])
    operation1.evaluate(scope)
    operation2.evaluate(scope)
    Print(Conditional(BinaryOperation(
          Number(4), '-', Number(4)), [], [
          BinaryOperation(Number(9), '/', Number(3)), Reference('var')
          ])).evaluate(scope)
    operation3 = FunctionDefinition('abs', Function(['a', 'b'], [
        Conditional(BinaryOperation(BinaryOperation(Reference('a'), '-',
                    Reference('b')), '>', Number(0)),
                    [
                    Print(BinaryOperation(Reference('a'), '-', Reference('b')))
                    ], [
            Print(BinaryOperation(Reference('b'), '-', Reference('a')))
        ])
    ]))
    operation4 = FunctionCall(Reference('abs'), [
        Number(23),
        UnaryOperation('-', Number(-30))
    ])
    operation5 = FunctionDefinition('fu', Function([], []))
    operation6 = FunctionCall(Reference('fu'), [])
    operation5.evaluate(scope)
    operation6.evaluate(scope)
    operation3.evaluate(scope)
    operation4.evaluate(scope)
    Print(BinaryOperation(Number(5), '&&', Number(6))).evaluate(scope)
    Print(BinaryOperation(Number(3), '<', Number(5))).evaluate(scope)


if __name__ == "__main__":
    main()

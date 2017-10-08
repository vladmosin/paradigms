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
        self.values = {}
        if parent is not None:
            for key in parent.values:
                self.values[key] = parent.values[key]

    def __getitem__(self, key):
        if key in self.values:
            return self.values[key]

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
            if self.if_false is None or not self.if_false:
                return Number(0)
            else:
                for statement in self.if_false:
                    res = statement.evaluate(scope)
                return res
        else:
            if not self.if_true:
                return Number(0)
            else:
                for statement in self.if_true:
                    res = statement.evaluate(scope)
                return res


class Print:
    def __init__(self, expr):
        self.expr = expr

    def evaluate(self, scope):
        num = self.expr.evaluate(scope)
        if type(num) == int:
            print(num)
            return Number(num)
        else:
            print(num.value)
            return num


class Read:
    def __init__(self, name):
        self.name = name

    def evaluate(self, scope):
        value = int(input())
        scope[self.name] = value
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
        res = Number(0)
        for state in function.body:
            res = state.evaluate(call_scope)
        return res


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
        if self.op == "+":
            return Number(self.lhs.evaluate(scope).value +
                          self.rhs.evaluate(scope).value)
        if self.op == "-":
            return Number(self.lhs.evaluate(scope).value -
                          self.rhs.evaluate(scope).value)
        if self.op == "*":
            return Number(self.lhs.evaluate(scope).value *
                          self.rhs.evaluate(scope).value)
        if self.op == "/":
            return Number(self.lhs.evaluate(scope).value //
                          self.rhs.evaluate(scope).value)
        if self.op == "%":
            return Number(self.lhs.evaluate(scope).value %
                          self.rhs.evaluate(scope).value)
        if self.op == "==":
            if self.lhs.evaluate(scope) == self.rhs.evaluate(scope):
                return Number(1)
            else:
                return Number(0)
        if self.op == "!=":
            if self.lhs.evaluate(scope) == self.rhs.evaluate(scope):
                return Number(0)
            else:
                return Number(1)
        if self.op == "<":
            if self.lhs.evaluate(scope).value < self.rhs.evaluate(scope).value:
                return Number(1)
            else:
                return Number(0)
        if self.op == ">":
            if self.lhs.evaluate(scope).value > self.rhs.evaluate(scope).value:
                return Number(1)
            else:
                return Number(0)
        if self.op == "<=":
            if self.lhs.evaluate(scope).value <=\
               self.rhs.evaluate(scope).value:
                return Number(1)
            else:
                return Number(0)
        if self.op == ">=":
            if self.lhs.evaluate(scope).value >=\
               self.rhs.evaluate(scope).value:
                return Number(1)
            else:
                return Number(0)
        if self.op == "<":
            if self.lhs.evaluate(scope).value <\
               self.rhs.evaluate(scope).value:
                return Number(1)
            else:
                return Number(0)
        if self.op == "&&":
            if self.lhs.evaluate(scope).value != 0 and\
               self.rhs.evaluate(scope).value != 0:
                return Number(1)
            else:
                return Number(0)
        if self.op == "||":
            if self.lhs.evaluate(scope).value != 0 or\
               self.rhs.evaluate(scope).value != 0:
                return Number(1)
            else:
                return Number(0)
        return Number(0)


class UnaryOperation:
    def __init__(self, op, expr):
        self.op = op
        self.expr = expr

    def evaluate(self, scope):
        if self.op == "-":
            return Number(0 - self.expr.evaluate(scope).value)
        if self.op == "!":
            if self.expr.evaluate(scope).value != 0:
                return Number(0)
            else:
                return Number(1)
        return Number(0)


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


if __name__ == "__main__":
    main()

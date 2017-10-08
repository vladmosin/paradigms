class Number:
    def __init__(self, value):
        self.value = value

    def evaluate(self, scope):
        return self

    def __repr__(self):
        return "Number({})".format(self.value)

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


class Conditional:
    def __init__(self, condition, if_true, if_false=None):
        self.condition = condition
        self.if_true = if_true
        self.if_false = if_false

    def evaluate(self, scope):
        if self.condition.evaluate(scope).value == 0:
            if self.if_false is None:
                return Number(0)
            else:
                return self.if_false.evaluate(scope)
        else:
            return self.if_true.evaluate(scope)


class Print:
    def __init__(self, expr):
        self.expr = expr

    def evaluate(self, scope):
        num = self.expr.evaluate(scope)
        print(num)
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
        function = fun_expr(scope)
        call_scope = Scope(scope)
        while arg in function.args and value in args:
            scope[arg] = value
        return function.evaluate(call_scope)


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
    cond_check = Conditional(Number(5),
                             BinaryOperation(Reference('var'), '-',
                                             Number(-5)))
    cond_check_result = cond_check.evaluate(scope)
    Print(cond_check_result).evaluate(scope)


if __name__ == "__main__":
    main()

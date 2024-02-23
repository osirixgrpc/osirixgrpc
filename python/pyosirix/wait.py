from python.pyosirix.exceptions import WaitException

#TODO wait for interface to be exposed
class Wait(object):

    def __init__(self, value: float, max_value : float) -> None:
        self.value = value
        self.max_value = max_value

    def increment_by(self, value : float) -> float:
        self.value = self.value + value
        if(self.value > self.max_value):
            raise WaitException("Exceeded Value of " + str(self.max_value) + ". Current Value :" + str(self.value))
        return self.value

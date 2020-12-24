 def printFunction() :
    print("Hello, World!")

printFunction()

def argsFunction(username, greeting) :
    print("Hello %s" % username)
    print(greeting)

argsFunction("Thunderdome32", "Hi how are you?")

def returnFunction(a, b) :
    sum_two = a + b
    return sum_two

print(returnFunction(3,4))

print

# Modify this function to return a list of strings as defined above
def list_benefits():
    listB = []
    listB.append("More organized code")
    listB.append("More readable code")
    listB.append("Easier code reuse")
    listB.append("Allowing programmers to share and connect code together")
    return listB

# Modify this function to concatenate to each benefit - " is a benefit of functions!"
def build_sentence(benefit):
    string = " is a benefit of functions!"
    string1 = benefit + string
    return string1

def name_the_benefits_of_functions():
    list_of_benefits = list_benefits()
    for benefit in list_of_benefits:
        print(build_sentence(benefit))

name_the_benefits_of_functions()

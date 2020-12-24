import datetime
# Define a class in python
class Person:
    def __init__(self, name, age):
    # Define attributes
        self.name = name
        self.age = age
    def __call__(self, name):
        print(name)
    # Define methods
    def calculate_birthyear(self):
        return datetime.datetime.now().year - self.age
    def get_firstname(self):
        return self.name.split(' ')[0]
    def get_surname(self):
        return self.name.split(' ')[-1]

# Create an object
person = Person("Anakin skywalker", 20)
another_person = Person("Luke Skywalker", 18)

print(person.get_firstname())
print(Person.get_firstname(person))
print(another_person.get_firstname())
print(person.get_surname())
print(person.calculate_birthyear())
# Use the object as argument in method
print(Person.get_firstname(person))
# Objects have state but classes don't

# __dict__ of objects
print(person.__dict__)

# Assigning functions to variables
def say_hello(name):
    return "Hello, " + name

var = say_hello

# Pass functions to functions
def func(funcname):
    return funcname("Yoda")

print(func(say_hello))


# Functions Arguments: objects
def change_name(obj):
    obj.name = "Yoda"
print(person.name)
change_name(person)
print(person.name)

# Some other mutable data types
# Lists
# Dict
# Set

# Function Arguments : Mutable Objects
li = [1,3,4]
def change_first(list_arg):
    list_arg[0] = 2
change_first(li)
#print(li)
# Looping through container of mutable objects
li = [[1,2], [2,3]]
for el in li:
    el[1] = 32
#print(li)
# Some of the immutable data types
# Int
# Float
# String
# Tuple

# Python id function
a = "a"
b = a
c = "a"
print(id(a), id(b), id(c), sep="\n")
# However:
a = "dogA"
f = "dog"
d = "dog"
c = d + "A"
print(id(a), id(c), sep="\n")
# So, be careful when using `is` in python
if a is c:
    print(True)
# function arguments: Immutable objects
def change(obj):
    obj += "Hello"
    #print(obj)
d = "dog"
change(d)
#print(d)
# Looping through immutable objects
li = ["A", "B"]
for el in li:
    el += "Hello"
print(li)
# How can we make this work?
for i in range(len(li)):
    li[i] += "Hello"
print(li)

# What is a module in python
from utilities import say_hello, Printer
say_hello()

# import modules in python
printer = Printer(2)
printer.create_print_job("Print something", pages=2)
printer.create_print_job("Print something", pages=2)
# Python FileIO

# Open a file for reading
f = open("some.txt", "r")
# Read all the text from a file
string = f.read()
# Read line by line with a loop
for line in f:
    print(line)
    
# Read a single line from the file
string = f.readline()
print(string)
# Read all the lines from a file into a list
print(f.readlines())

# open file for writing/appending
f = open("some.txt", 'a')
# Write something to a file
f.write("A new line")
# Write the following list to the file you just opened
li = ["This", "is", "a", "list", "of"]
for element in li:
    f.write(element+"\n")
# Pickle
import pickle
pickle.dump(person, open("class_file.txt", "wb"))
anakin = pickle.load(open("class_file.txt", "rb"))
print(anakin.name)











# Handling errors and exceptions in python
# Exceptions in python


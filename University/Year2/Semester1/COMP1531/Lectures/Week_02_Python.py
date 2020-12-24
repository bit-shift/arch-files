# Python strings are immutable
s = "Dog"
s = s + "B"
# Python Data Structures
# Declare lists in python
lista = ["Eggs", "Milk", "Jelly", "Fish"]
listb = [1,2,3,4]
listc = [2.9, 3.9, 2.1]
#print(lista, listb, listc, sep="\n")
# List with mixed types
lista = ["A", 1, 3.0]
# Check size of a list
print(len(lista))
# Magic with list indexing, slicing, steps
# list[start:end:step]
listb = [1, 2, 3, 4, 5, 6, 7]
list_sliced = listb[3:6]
list_all = listb[:]
list_all[0] = 9
print(listb[-1])
print(listb[-2])
# Slicing a list will create a new list
#========================================
# Exercise: Print a list in reverse order
print(listb[::-1]) 
#========================================  
# Step count 2 with reverse
print(listb[::-2])
# Append to a list
listb.append("hello")
listb.append("hello")
# Pop last element from a list
#[1,2,3] -> 4
last_el = listb.pop()
# remove items from a list
listb.remove("hello")
# list insert
listb.insert(3, "Hello")
# loop through lists - using index
for i in range(len(listb)):
    print(listb[i])
# loop through lists using magic
for element in listb:
    print(element)
# List concatenation
print(lista + listb)
# Update values in python lists
listb[0] = "comp1531"
print(listb)
# li now has the same reference as a
# so if li changes, a will change as well
li = listb[::]

# Spot the error
#li = [1,4,2,5,1,3]
#flag = True
#sorting_steps = []
#while flag:
#    flag = False
#    for i in range(len(li) - 1):
#        if li[i] > li[i+1]:
#            temp = li[i+1]
#            li[i+1] = li[i]
#            li[i] = temp
#            flag = True
#    sorting_steps.append(li)
#
#for step in sorting_steps:
#    print(step)
# Lists inside lists
listb = [[1,2,3], [3], 3, [[2,3], 3]]
print(listb)
# loop through list inside lists
for el in listb:
    print(el)

#for element in li:
#    print(element, end=" ")
#=====================================
a = [[1,2,3], [1], 2, [[1,2,3],3], 4]
for el in a:
    print(el)
#=====================================
 
#List comprehensions

# Python Tuples
a = (1,2,"hello")
# What are they normally used for?
# Tuple unpacking
a,b,c = (1,2,"hello")


#==============================================================
# Exercise: We need to store employee information of a bank.
#           Consider the following employees:
#           Name: A, id: 1
#           Name: B, id: 2
#           Name: C, id: 3
#==============================================================
employee_info = [('A',1),('B',2),('C',3)]
# Python Sets
s = {1,2,3,3,3,4,4}
b = {1,2}
# And, or and exclude
or_ed = s | b
and_ed = s & b
diff_ed = s - b
# How do they work?
#key -> hashing_function(key) -> stable_int
# "name" -> 2
# [0,0,1,0,0,0,0,0,0,0]
# Two keys might end up with the same stable int
# Hashmaps account for that in different ways
# You can always assume that the key, value
# pairs you store will always be the same


# Python Dictionaries (Hashmaps)
# Declaration
dictionary = {}
dictionary = {"name":1, "name2":3} 
dictionary["name"] = 1
dictionary[2] = 4
dictionary["name2"] = [1,2,3]
dictionary[(1,2,3)] = [1,2,3,4]

# Retrieve value
print(dictionary[(1,2,3)])



# loop through dicts
for el in dictionary:
    print(el)
# use keys()
for el in dictionary.keys():
    print(el)
# use values()
for el in dictionary.values():
    print(el)
# use items()
for key, val in dictionary.items():
    print(key, val)
    

#==============================================================
# Exercise: We need to store employee information of a bank.
#           Consider the following employees:
#           Name: A, id: 1, sal = 20000
#           Name: B, id: 2, sal = 30000
#           Name: C, id: 3, sal = 50000
#==============================================================
dictionary = {("A", 1):20000, ("B", 2):30000}
# Functions in python

#def func_name(a,b):
#    do something

# Return values

# Function args
def plus_one(n):
    return n + 1

print(plus_one(1))


# Default values
def plus_one_1(a,b,n=1):
    return n + 1

print(plus_one_1(a,b))

# flexible args
def plus_one_2(n, *args, **keywords):
    print(n)
    print(args)
    print(keywords)
plus_one_2(2, 3, 4, 5, 6, 7, name="Some name", something=3)
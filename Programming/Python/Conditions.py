x = 2
print(x==2)
print(x==3)
print(x<3)

if x == 2:
    print("x equals two!")
else:
    print("x does not equal to two.")

name = "Adam"
age = 23
if name == "John" and age == 23 :
    print("Your name is John and you are 23 years old")
if name == "John" or name == "Rick" :
    print("Your name is either John or Rick")

if name in ["John","Rick"] :
    print("Your name is either John or Rick")
elif name in ["Adam","Eloise"] :
    print("Your name is either Adam or Eloise")
else :
    print("Your name matches none of the above")

x = [1,2,3]
y = [1,2,3]
print(x == y)
print(x is y)

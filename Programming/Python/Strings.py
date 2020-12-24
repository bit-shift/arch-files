name = "John"
print("Hello, %s!" % name)

name = "John"
age = 23
print("%s is %d years old." % (name,age))

mylist = [1,2,3]
print("List: %s" % mylist)

data = ("John", "Doe", 53.44)
format_string = "Hello"
print(format_string + " %s %s. Your current balance is $%.2f." % (data[0], data[1], data[2]))

print

data = ("John", "Doe", 53.44)
format_string = "Hello %s %s. Your current balance is $%s."
print(format_string % data)

string = "hello world!"
print(len(string))
print(string.index("o"))
print(string.count("l"))
print(string[3:7])
print(string[3:7:2])
print(string[3:7:1])
print(string[::-1])
print(string.upper())
print(string.lower())
print(string.startswith("hello"))
print(string.endswith("a"))

words = string.split(" ")
for i in words:
    print(i)

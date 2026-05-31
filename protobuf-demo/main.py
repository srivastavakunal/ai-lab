import person_pb2

book = person_pb2.AddressBook()

p1 = book.poeple.add()
p1.name = "PiKu"
p1.age = 15
p1.email = "srivastava.kunal@gmail.com"

data = book.SerializeToString()

print("Searlizie bytes:")
print(data)

new_book = person_pb2.AddressBook()
new_book.ParseFromString(data)

print("\nDeserialized object:")
print(new_book)

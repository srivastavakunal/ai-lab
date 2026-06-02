import person_pb2


def main():
    person = person_pb2.Person()
    person.name = "PiKu"
    person.age = 15
    person.email = "srivastava.kunal@gmail.com"

    data = person.SerializeToString()

    with open("person.bin", "wb") as f:
        f.write(data)

    print("Wrote person.bin")
    print(f"Serialized size: {len(data)} bytes")


if __name__ == "__main__":
    main()

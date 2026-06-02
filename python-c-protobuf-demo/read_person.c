#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "pb_decode.h"
#include "person.pb.h"

int main(void)
{
    FILE *file = fopen("person.bin", "rb");
    if (file == NULL) {
        perror("Failed to open person.bin");
        return 1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    if (file_size <= 0 || file_size > 1024) {
        fprintf(stderr, "Invalid file size: %ld\n", file_size);
        fclose(file);
        return 1;
    }

    uint8_t *buffer = malloc(file_size);
    if (buffer == NULL) {
        perror("Failed to allocate buffer");
        fclose(file);
        return 1;
    }

    size_t bytes_read = fread(buffer, 1, file_size, file);
    fclose(file);

    if (bytes_read != (size_t)file_size) {
        fprintf(stderr, "Failed to read full file\n");
        free(buffer);
        return 1;
    }

    Person person = Person_init_zero;

    pb_istream_t stream = pb_istream_from_buffer(buffer, file_size);
    bool status = pb_decode(&stream, Person_fields, &person);

    free(buffer);

    if (!status) {
        fprintf(stderr, "Decode failed: %s\n", PB_GET_ERROR(&stream));
        return 1;
    }

    printf("Decoded Person in C:\n");
    printf("Name : %s\n", person.name);
    printf("Age  : %d\n", person.age);
    printf("Email: %s\n", person.email);

    return 0;
}

import sys
import random
import string

letters = string.ascii_lowercase

def genRandomString(length):
    return ''.join(random.choice(letters) for _ in range(length))

if (len(sys.argv) != 4):
    print(sys.argv[0] + "<key length> <insert amount> <query amount>")
    exit(1)

key_length = int(sys.argv[1])
insert_amount = int(sys.argv[2])
query_amount = int(sys.argv[3])

print(f"Generating {insert_amount:,} random inserts of length {key_length}")
f = open("./data/rand_inserts", "w")
for _ in range(insert_amount):
    f.write(genRandomString(key_length) + "\n")
f.close()

print(f"Generating {insert_amount:,} random queries of length {key_length}")
f = open("./data/rand_queries", "w")
for _ in range(insert_amount):
    f.write(genRandomString(key_length) + "\n")
f.close()


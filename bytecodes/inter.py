class MontyInterpreter:
    def __init__(self):
        self.stack = []

    def execute(self, filename):
        try:
            with open(filename, 'r') as file:
                lines = file.readlines()
                for line_number, line in enumerate(lines, start=1):
                    self.process_line(line.strip(), line_number)
        except FileNotFoundError:
            print(f"Error: Can't open file {filename}")
            exit(1)

    def process_line(self, line, line_number):
        if not line or line.startswith('#'):
            return  # Ignore empty lines and comments

        tokens = line.split()
        opcode = tokens[0].lower()

        if opcode == 'push':
            self.push(tokens[1], line_number)
        elif opcode == 'pall':
            self.pall()
        else:
            print(f"L{line_number}: unknown instruction {opcode}")
            exit(1)

    def push(self, value, line_number):
        try:
            self.stack.append(int(value))
        except ValueError:
            print(f"L{line_number}: invalid argument for push")
            exit(1)

    def pall(self):
        print(self.stack)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python interpreter.py <filename>")
        exit(1)

    filename = sys.argv[1]
    interpreter = MontyInterpreter()
    interpreter.execute(filename)


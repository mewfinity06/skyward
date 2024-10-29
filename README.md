# Skyward

## A new langage by Ashton Sickler

### Working:
- [ ] Types
- [ ] Functions
- [ ] Structs
  - [ ] Compact
  - [ ] Loose
  - [ ] Enumerations
- [ ] Struct Member Functions

> ### Basic Types
>
> #### Int
> 
> #### Char
> 
> #### Float
> 
> #### None
>
> #### Void
>
> #### NULL

> ### Complex Types
> 
> #### Complex
>
> #### Struct
> * Compact
> * Loose
> * Enum

### Basic Syntax

```rust
use io; // used to call the IO standard library

mut A : Int;         // Calls a global Mutable
const B: Int = 10;   // Calls a global Constant

func Main(argc: Int, argv: Char*) : Int {
    io.print("Hello World!\n"); // Prints the string

    @A = 1; // Reassigns global A; the `@` is used to seperate
            // global variables from local variables
            // i.e. A and @A are different!

    // Control flow!
    if @A < @B {
        io.print("A is less than B\n");
    } else {
        io.print("B is less than A\n");
    }

    return 0; // Every function MUST have a return statement, 
              // even Main unless they return None
}
```

### Functions

#### Untyped functions

Untyped functions provide a quick and easy way to write a function that takes in no paramters!

```rust
// use statements and main function not included for clarity!

func Foo : None {
    io.print("Untyped functions are cool!");
}

func Bar : Char* {
    return "Untyped but a return??";
}

// Call to Foo
Foo();  // Note: functions calls, even Untyped functions 
        // MUST include parentheses

// Call to Bar
Bar(); // returns "Untyped but a return??"

```

#### Typed functions

Just like in anyother languages, Skyward has typed functions!

```rust
func Baz(name: Char*) : None {
    io.print("Hello, {name}!\n");
}

// Call to Baz
Baz("Skyward"); // prints "Hello, Skyward"

```

### Structs and Member functions

#### Basic Struct

Skyward does not have traditional OOP. When it comes to Structs in Skyward, think of Rust and Zig.

```rust
// Structs are Compact by default, but you can also specify!
struct Employee : Compact {
// Name of Member, Type of Member
    Status: EmployeeStatus, // See Enumerations
    Name:   Char*,
    ID:     Int,
}
```

#### Enumerations

```rust
struct EmployeeStatus : Enum {
// Enums start at 0, unless otherwise stated, steps by one whole value

    // Explicit start
    @start 0;
    // Explicit step
    @step 100;

    ADMIN,    // 0
    MANAGER,  // 100
    ENTRY,    // 200
    GUEST,    // 300
}
```

#### Member functions

Member functions can apply to ANY struct type: Compact, Enum, Loose, etc.

```rust
// Using Employee and Employee Status above

// Calling Employee function
Employee : impl {

    private mut ID_seed: Int = 0;


    // Creates a new Employee struct and sets all of it's attributes
    // accordingly.
    // The defer keyword activates after the return statement.
    pub func new(name: Char*, status: EmployeeStatus) : Employee {
        defer ID_seed++;
        return Employee {
            Name = name,
            Status = status,
            ID = ID_seed + status;
        }
    }

    // Self is assumed in Untyped Member Functions
    pub func get_name : Char* {
        return self.Name;
    }

    pub fn get_id : Int {
        return self.ID;
    }

    pub fn print : None {
        io.print("Name: {self.Name}\n");
        io.print("ID: {self.ID}");
        self.Status.print();
    }
}

EmployeeStatus : impl {

    pub print : None {
        switch(self) {
        ADMIN   => io.print("Admin"); break;
        MANAGER => io.print("Manager"); break;
        ENTRY   => io.print("Entry"); break;
        GUEST   => io.print("Guest"); break;
        else    => io.print("Unknown Status"); break; // Akin to default in C
        final   => io.print("\n"); // final always runs, unless an error occurs
        }
    }

}

```

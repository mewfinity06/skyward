# Skyward

## A new langage by Ashton Sickler

Simple reason? I got bored.
I was watching YouTube and stumbled upon [Lens_r's FUNCompiler series](https://www.youtube.com/watch?v=apFUyLupFgE&list=PLysa8wRFCssxGKj_RxBWr3rwmjEYlJIpa) and finally decided to try to write my own! 

If you have anything to contribute, I would love it! Criticism, comments, complaints, questions? Bring them on! Feel free to pull and add your own fucnctionality (As long as it complies with the License, of course). I believe in Open Source first.

I have inspiration from some of my favorite languages, (including Golang, Rust, C++)

#### Goals
- [ ] Split file into tokens
- [ ] Have a compile and simulate function
- [ ] 

### Note:

This language is a work in progress. Syntax and semantics are subject to change.
To see what is working, please check out Working!

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

> ### Keywords

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
              // even Main unless they return Void
}
```

### Control flow

#### For loops

#### While loops

### Functions

#### Untyped functions

Untyped functions provide a quick and easy way to write a function that takes in no paramters!

```rust
// use statements and main function not included for clarity!

func Foo : Void {
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
func Baz(name: Char*) : Void {
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

    pub fn print : Void {
        io.print("Name: {self.Name}\n");
        io.print("ID: {self.ID}");
        self.Status.print();
    }
}

EmployeeStatus : impl {

    pub print : Void {
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

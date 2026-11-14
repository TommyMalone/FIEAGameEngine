# FIEA Game Engine

A data-driven game engine core in C++17. I wrote it in 2019 as graduate coursework at the University of Central Florida’s Florida Interactive Entertainment Academy (FIEA) and extended it in 2020 with a family of red-black tree containers.

The engine's idea is that game objects are described in data. A JSON file describes a world, the engine builds the objects it names through factories, and their behavior is a tree of actions that the file also describes. The C++ classes underneath can be read and changed by name at runtime, so script and code share one object model.

This was an academic exercise in how an engine is built. It is the core of an engine and not a finished one, with no renderer and no game built on it.

## Where to start

If you want one piece of code that shows how I write C++, read **Datum**.

- `source/Library.Shared/Datum.h`, `Datum.inl`, and `Datum.cpp`
- `source/UnitTest.Library.Desktop/DatumTest.cpp`

Datum is a runtime-typed, dynamically sized array built on a discriminated union. Its element type is chosen at runtime from integer, float, vector, matrix, string, a pointer to a Scope, or a pointer to any RTTI object. It either owns its storage or sits over memory that another object owns, which is how a script reaches a C++ member variable. The header comments describe each function, and the test file exercises every type in both storage modes.

The natural second read is **Scope** (`Scope.h`, `Scope.cpp`, `ScopeTest.cpp`). A Scope is a table of named Datums, and a Datum can hold Scopes, so the two together form the tree that everything else in the engine is built on.

## What is in it

### The data model

| Class | What it does |
|---|---|
| `Datum` | A runtime-typed array with internal or external storage. The value type of the whole engine. |
| `Scope` | A table of name and Datum pairs with a pointer to its parent. Scopes inside Datums make a tree. |
| `Attributed` | A Scope whose entries point at the member variables of a C++ class, so the same object can be read from code and from data. Members a class declares are prescribed attributes. Entries added from data are auxiliary attributes. |
| `TypeManager` | The registry of each Attributed class's member signatures. |
| `RTTI` | A small runtime type system used for safe downcasts across the engine. |
| `Factory` | A templated abstract factory that also keeps the registry of concrete factories, so a class can be created from its name in a data file. |

### Containers

All written from scratch, each with iterators and its own unit tests.

| Class | What it does |
|---|---|
| `Vector` | A dynamic array in contiguous memory. |
| `SList`, `DList` | Singly and doubly linked lists. |
| `Stack` | A stack adapter. |
| `UnorderedMap` | A hash map with separate chaining, a Vector of SList buckets, and a replaceable hash functor. |
| `RedBlackTree` | A red-black tree templated on a traits class. |
| `OrderedSet`, `OrderedMultiSet`, `OrderedMap`, `OrderedMultiMap` | Four ordered containers, each a thin class over `RedBlackTree` with a different traits class. |

### JSON parsing

| Class | What it does |
|---|---|
| `JsonParseMaster` | Walks a JSON document and offers each value to a chain of helpers until one handles it. |
| `IJsonParseHelper` | The interface a helper implements for one grammar. |
| `ScopeJsonParseHelper` | The helper that builds a tree of Scopes from a file, creating each named class through its factory. |

The files under `source/UnitTest.Library.Desktop/Content` show the format. `WorldAction.json` describes a world, a sector, an entity, and a nested list of actions.

### The world and its actions

| Class | What it does |
|---|---|
| `World`, `Sector`, `Entity` | The object hierarchy. A world holds sectors, a sector holds entities, and each one updates its children every frame. |
| `Action` | The base class for a unit of behavior that an entity, a sector, or a world runs on update. |
| `ActionList` | An action that runs a list of actions in order. |
| `ActionListWhile` | A loop, with preamble actions, a condition, a body, and increment actions. |
| `ActionIncrement` | Finds an attribute by name and increments it. |
| `CreateAction`, `DestroyAction` | Create an action by class name through its factory, or mark one for removal at the end of the frame. |
| `GameClock`, `GameTime`, `WorldState` | The clock, and the state passed down the update call. |

### Events

| Class | What it does |
|---|---|
| `Event<T>` | A typed event carrying a message of type `T`, with a subscriber list for each message type. |
| `EventPublisher` | The base class that delivers an event to its subscribers. |
| `EventQueue` | Holds events with a delay and delivers the expired ones on update. Delivery runs through `std::async`, and the queue and the subscriber lists are guarded by mutexes. |
| `IEventSubscriber` | The interface a subscriber implements. |
| `ActionEvent` | An action that queues an event from data. |
| `Reaction`, `ReactionAttributed` | An action list that is also a subscriber, so a data file can say which actions run when an event of a given subtype arrives. |

## Layout

| Path | Contents |
|---|---|
| `source/Library.Shared` | The engine. 91 source files. |
| `source/Library.Desktop` | The project that builds the engine as a static library. |
| `source/UnitTest.Library.Desktop` | The unit tests and the JSON files they load. |
| `source/Game.OpenGL.Desktop`, `source/Game.DirectX.Desktop` | Starter projects for a game executable, one for each graphics API. |
| `external.dependencies` | Third-party headers and binaries: GLFW, gl3w, GLM, the Guidelines Support Library, and JsonCpp. |
| `Shared.props` | Build settings shared by every project. |

## Tests

19 test files with 218 test methods, written with the Microsoft C++ Unit Test Framework. Every test file takes a snapshot of the debug heap before each test and compares it afterward, so a leak fails the test.

## Building

The solution is `FIEAGameEngine.sln`, set up for Visual Studio 2019 (toolset v142) on Windows, in C++17, at warning level 4 with warnings treated as errors. The tests run from Visual Studio's Test Explorer.

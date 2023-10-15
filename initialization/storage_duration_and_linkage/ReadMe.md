# Storage duration and linkage

## Storage duration
The storage duration is the property of an object that defines the minimum potential lifetime of the storage containing the object. The storage duration is determined by the construct used to create the object.

| Storage duration | Explanation                                                   |
| ---------------- | ------------------------------------------------------------- |
| *automatic*      | Automatic means that the storage is allocated at the <br />   |
|                  | start of the scope. Most local variables have automatic       |
|                  | storage duration (except those declared as static, extern,    |
|                  | or thread_local)                                              |
| *static*         | The storage for an object is allocated when the program       |
|                  | begins (usually before the main() functions starts) and       |
|                  | deallocated when the program ends. There's only one instance  |
|                  | of such an object in the whole program.                       |
| *thread*         | The storage for an object is tied to a thread: it's started   |
|                  | when a thread begins and is deallocated when the thread ends. |
|                  | Each thread has its own "copy" of that object.                |
| *dynamic*        | The storage for an object is allocated and deallocated using  |
|                  | explicit dynamic memory allocation functions. For example, by |
|                  | the call to new/delete.                                       |

## Linkage
A name is said to have linkage when it can denote the same object, reference, function, type, template, namespace, or value as a name introduced by a declaration in another scope.

| Linkage            | Explanation                                              |
| ------------------ | -------------------------------------------------------- |
| *external linkage* | External means that the name can be referred to from the |
|                    | scopes in the same or other translation units. Non-const |
|                    | global variables have external linkage by default.       |
| *module linkage*   | Available since C++20. A name can be referred in scopes  |
|                    | of the same module or module units.                      |
| *internal linkage* | A name can be referred to from the scopes in the same    |
|                    | translation units. For example, a static, const, and     |
|                    | constexpr global variables have internal linkage.        |
| *no linkage*       | Cannot be referred from other scopes.                    |
| *language linkage* | Allows interoperability between different programming    |
|                    | languages, usually with C. For example, by declrating    |
|                    | extern "C"                                               |
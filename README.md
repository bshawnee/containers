# containers
## Description:
in this project, I implemented standard containers and iterators for them:
- map
- set
- vector
- stack
- pair
- bidirectional iterator
- random access iterator
- reverse iterator
## usage:
just include in project.
## time:
tests used: https://github.com/divinepet/ft_containers-unit-test
- stack:

|         | std   | my   |
| :---:   | :-:   | :-:  |
| push    | 234ms | 67ms |
| pop     | 47ms  | 14ms |
| ct      | 79ms  | 25ms |

- vector:

|              | std     | my     |
| :---:        | :-:     | :-:    |
| ct           | 87ms    | 172ms  |
| ct std it    | 87ms    | 85ms   |
| resize       | 822ms   | 1311ms |
| assign       | 584ms   | 630ms  |
| asign std it | 345ms   | 408ms  |
| push_back    | 1191ms  | 423ms  |
| insert(value)| 192ms   | 157ms  |
| insert(fill) | 287ms   | 112ms  |

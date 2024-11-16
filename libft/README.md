<p align="center">
  <img src="https://github.com/pibouill/42-project-badges/blob/main/badges/libfte.png" alt="ready to help"/>
</p>

<p align="center">
	<img alt="GitHub code size in bytes" src="https://img.shields.io/github/languages/code-size/pibouill/libft">
</p>

# Libft
> This project is about understanding the way these functions work, implementing and learning to use them. You will create your own library. It will be
helpful since you will use it in your next C school assignments.

## libc functions
> Your functions will have the same prototypes and implement the same behaviors as the originals. They must comply
with the way they are defined in their man. The only difference will be their names.

### C types
+ isalpha	
+ isdigit
+ isalnum
+ isascii
+ isprint
+ toupper
+ tolower

### Strings
+ strlen
+ strlcpy
+ strlcat
+ strchr
+ strrchr
+ strncmp
+ strnstr
+ strdup

### Strings - Memory
+ memset
+ bzero
+ memcpy
+ memmove
+ memchr
+ memcmp

### stdlib
+ atoi
+ calloc

## Additional functions
> In this second part, you must develop a set of functions that are either not in the libc,
or that are part of it but in a different form.

### put_functions
+ ft_putchar_fd
  >Outputs a character to the given file descriptor.
+ ft_putstr_fd
  >Outputs a string to the given file descriptor.
+ ft_putnbr_fd
  >Outputs an integer to the given file descriptor.
+ ft_putendl_fd
  >Outputs a string to the given file descriptor followed by a newline.
___
+ substr
  >Allocates with malloc and returns a substring from the given string.
+ strjoin
  >Allocates with malloc and returns a new string which is the result of the concatenation of two strings.
+ strtrim
  >Allocates with malloc and returns a copy of a string with the characters specified in 'set' removed from the beginning and the end of the string.
+ split
  >Allocates with malloc and returns an array of strings obtained by splitting a string using the character 'c' as a delimiter.
+ itoa
  >Allocates with malloc and returns a string representing the integer received as an argument (negative numbers handled).
+ strmapi
  >Applies the function ’f’ to each character of the
string ’s’, and passing its index as first argument
to create a new string malloc resulting
from successive applications of ’f’.
+ striteri
  >Applies the function ’f’ on each character of
the string passed as argument, passing its index
as first argument. Each character is passed by
address to ’f’ to be modified if necessary.

## Lists
```c
typedef struct	s_list
{
	void			*content;
 	struct s_list		*next;
}					t_list;
```
+ lstnew
  >Allocates with malloc and returns a new node. 
+ lstadd_front
  >Adds a node to the beginning of a list.
+ lstsize
  >Counts the number of nodes in a list.
+ lstlast
  >Returns the last node of a list.
+ lstadd_back
  >Adds a node to the end of a list.
+ lstdelone
  >Frees the memory of a node's content using the 'del' function and frees the node.
+ lstclear
  >Deletes and frees the given node and every successor of that node, using the function 'del' and free.
+ lstiter
  >Iterates a list and applies a function on the content of each node.
+ lstmap
  >Iterates a list and applies a function on the content of each node. Creates a new list resulting of the successive applications of the function.

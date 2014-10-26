package	main

import	(
	"fmt"
)

func main() {
	classname := "distribute system"

	fmt.Println("Hello, ", classname)

	fmt.Println("Hello half-class: ", classname[0:3])

	fooname := classname[0:3]
	fmt.Println("Hello fooclass: ", fooname)

//	classname[0] = 'C'       // Strings are immutable!
//	fooname[0] = 'C'         // A slice refs the original

	buf := []byte(classname)// Copy and modify the string
	buf[0] = byte('C')
	fmt.Println(string(buf))// Cistribute system
}
package	main

import	(
	"fmt"
	"net"
	"os"
)

type myConn struct {	// declare a struct
	conn net.Conn
	prefix string
}


func handleConn(mconn *myConn){// need to know the type of the parameter
	// Start a "goroutine"
	fmt.Println("Reading once from connection")

	var buf[1024] byte
	n,err := mconn.conn.Read(buf[:])// slicing?
	if err != nil {
		fmt.Println("Error on read: ", err)
		os.Exit(-1)
	}

	fmt.Println(mconn.prefix, ": ", string(buf[0:n]))
	mconn.conn.Close()	
}


func main() {
	ln, err := net.Listen("tcp", ":15440")
	if err != nil{
		fmt.Println("Error on listen: ", err)
		os.Exit(-1)
	}
	connNumber := 0
	for {	// like c for(;;)
		fmt.Println("Waiting for a connection via Accept")
		conn, err := ln.Accept()	// err doubly-declared?!
		if err != nil {
			fmt.Println("Error on accept: ", err)
			os.Exit(-1)
		}

		mconn := &myConn{	// asign a struct
			conn: conn,		// need a coma
			prefix: fmt.Sprintf("%d sys", connNumber), //need a comma
		}
		go handleConn(mconn)
	}
	fmt.Println("Exiting")
}
package main

import	(
	"fmt"
	"time"
)

type myMsg struct {
	seqNum int
	message string
}

func main() {
	fmt.Println("Go channel starting.")

	ch := make(chan *myMsg)	// unbuffered

	go chanSender(ch, "cs1")
	go chanSender(ch, "cs2")
	go chanSender(ch, "cs3")

	for msg := range ch{
		fmt.Println("Message", msg.seqNum, ":", msg.message)
	}
}

func chanSender(out chan *myMsg, prefix string){	//out chan<- *myMsg is fine too
	seqNum := 0
	for i := 0; i < 5; i++ {
		time.Sleep(1*time.Second)
		out <- &myMsg{seqNum, fmt.Sprintf("%s: %s", prefix, "moo")}
		seqNum++
	}
	close(out)
}
// Go channel starting.
// Message 0 : cs1: moo
// Message 0 : cs3: moo
// Message 0 : cs2: moo
// Message 1 : cs1: moo
// Message 1 : cs2: moo
// Message 1 : cs3: moo
// Message 2 : cs1: moo
// Message 2 : cs3: moo
// Message 2 : cs2: moo
// Message 3 : cs1: moo
// Message 3 : cs2: moo
// Message 3 : cs3: moo
// Message 4 : cs1: moo(only one 4)
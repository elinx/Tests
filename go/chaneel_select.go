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

	ch1 := make(chan *myMsg)	// unbuffered
	go chanSender(ch1, "cs1")

	ch2 := make(chan *myMsg)	// unbuffered
	go chanSender(ch2, "cs2")

	for {
		select {
		case msg := <-ch1:
			fmt.Println("CH1: ", msg.seqNum, ":", msg.message)
		case msg := <-ch2:
			fmt.Println("CH2: ", msg.seqNum, ":", msg.message)
		}
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
// CH1:  0 : cs1: moo
// CH2:  0 : cs2: moo
// CH1:  1 : cs1: moo
// CH2:  1 : cs2: moo
// CH1:  2 : cs1: moo
// CH2:  2 : cs2: moo
// CH1:  3 : cs1: moo
// CH2:  3 : cs2: moo
// CH1:  4 : cs1: moo
// panic: runtime error: invalid memory address or nil pointer d
// [signal 0xc0000005 code=0x0 addr=0x0 pc=0x401285]
// 
// goroutine 16 [running]:
// runtime.panic(0x4c9020, 0x55de42)
//         c:/go/src/pkg/runtime/panic.c:279 +0x11f
// main.main()
//         D:/github/Tests/go/chaneel_select.go:25 +0x285
// 
// goroutine 19 [finalizer wait]:
// runtime.park(0x415770, 0x561c80, 0x560689)
//         c:/go/src/pkg/runtime/proc.c:1369 +0xac
// runtime.parkunlock(0x561c80, 0x560689)
//         c:/go/src/pkg/runtime/proc.c:1385 +0x42
// runfinq()
//         c:/go/src/pkg/runtime/mgc0.c:2644 +0xdd
// runtime.goexit()
//         c:/go/src/pkg/runtime/proc.c:1445
// 
// goroutine 21 [chan send]:
// main.chanSender(0xc08200a360, 0x4dcd30, 0x3)
//         D:/github/Tests/go/chaneel_select.go:36 +0x1c7
// created by main.main
//         D:/github/Tests/go/chaneel_select.go:20 +0x170
// exit status 2
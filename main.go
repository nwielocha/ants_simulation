package main

import (
	"flag"
	"fmt"
	"math/rand"
	"os"
	"os/exec"
	"time"
)

const X = 100
const Y = 25

type TPozycja struct {
	x, y   int
	powrot int
}

type Wspolrzedne []TPozycja

type TUstawienia struct {
	populacja   int
	powtorzenie int // liczba przerysowan ekreanu
	opoznienie  int
	jedzenie    int // liczba jedzenia
	gniazdo     int // wielkosc mrowiska
}

// Liczenie wielkosci mrowiska
func generacja(start, i int) func() int {
	return func() int {
		start = start + i
		return start
	}
}

// Generacja planszy
func granice(X, Y int) {
	for i := 0; i <= Y; i++ {
		for j := 0; j <= X; j++ {
			if i == 0 || i == Y {
				fmt.Printf("x")
			} else {
				if j == 0 || j == X {
					fmt.Printf("x")
				} else {
					fmt.Printf(" ")
				}
			}
		}
		println()
	}
}

func setup(CFG *TUstawienia) {
	flag.IntVar(&CFG.populacja, "populacja", 10, "Wielkosc populacji mrowek")
	flag.IntVar(&CFG.powtorzenie, "powtorzenia", 1000, "Liczba powtorzen")
	flag.IntVar(&CFG.opoznienie, "opoznienie", 99999999, "Opoznienie")
	flag.IntVar(&CFG.jedzenie, "ilosc", 200, "Ilosc jedzenia")
	flag.IntVar(&CFG.gniazdo, "wielkosc", 10, "Wielkosc gniazda")
	flag.Parse()
	rand.Seed(time.Now().UnixNano())
}

func stworzMrowke(m_count int) Wspolrzedne {
	col := make(Wspolrzedne, m_count)
	for i := range col {
		col[i].x = rand.Intn(X-1) + 2
		col[i].y = rand.Intn(Y-1) + 2
		col[i].powrot = 0
	}

	return col
}

func stworzJedzenie(j_count int) Wspolrzedne {
	jedzenie := make(Wspolrzedne, j_count)

	for i := range jedzenie {
		jedzenie[i].x = rand.Intn(X-1) + 2
		jedzenie[i].y = rand.Intn(Y-1) + 2
		jedzenie[i].powrot = 1
	}

	return jedzenie
}

func stworzGniazdo(g_count, max_g_count int) Wspolrzedne {
	mrowka := make(Wspolrzedne, max_g_count)

	for i := 0; i < g_count; i++ {
		if i == 0 {
			mrowka[i].x = rand.Intn(X-1) + 2
			mrowka[i].y = rand.Intn(Y-1) + 2
			mrowka[i].powrot = 1
		} else {
			mrowka[i].x = mrowka[i-1].x + 1 - rand.Intn(3)
			mrowka[i].y = mrowka[i-1].y + 1 - rand.Intn(3)
			mrowka[i].powrot = 1

			for j := 1; j <= i; j++ {
				if mrowka[i].x == mrowka[i-j].x && mrowka[i].y == mrowka[i-j].y || mrowka[i].x <= 1 || mrowka[i].y <= 1 || mrowka[i].x > X-1 || mrowka[i].y > Y-1 {
					mrowka[i].powrot = 0
					i = i - 1
					j = i
				}
			}
		}
	}

	return mrowka
}

// Czyszczenie ekranu dla darwina, linuxa oraz windowsa
func clearScreen() {
	cmd := exec.Command("clear", "cmd", "/c", "cls")
	cmd.Stdout = os.Stdout
	cmd.Run()
}

func main() {
	clearScreen()
	granice(X, Y)

	var config TUstawienia
	setup(&config)

	gen := generacja(config.gniazdo, 1)
	mrowka := stworzMrowke(config.populacja)
	jedzenie := stworzJedzenie(config.jedzenie)
	gniazdo := stworzGniazdo(config.gniazdo, config.gniazdo+config.jedzenie)

	// Wyswietlenie jedzenia
	for i := range jedzenie {
		fmt.Printf("\u001b[32m\x1B[%d;%df%s\u001b[0m", jedzenie[i].y, jedzenie[i].x, "o")
	}

	// Glowna petla
	for i := 0; i < config.powtorzenie; i++ {
		// Wyswietlanie
		for i := range mrowka {
			if mrowka[i].powrot == 0 {
				fmt.Printf("\u001b[33m\x1B[%d;%df%s\u001b[0m", mrowka[i].y, mrowka[i].x, ".")
			} else {
				fmt.Printf("\u001b[31m\x1B[%d;%df%s\u001b[0m", mrowka[i].y, mrowka[i].x, ".")
			}
		}

		for i := range gniazdo {
			fmt.Printf("\u001b[35m\x1B[%d;%df%s\u001b[0m", gniazdo[i].y, gniazdo[i].x, "x")
		}

		time.Sleep(time.Duration(config.opoznienie))

		// Czyszczenie
		for i := range mrowka {
			fmt.Printf("\x1B[%d;%df%s", mrowka[i].y, mrowka[i].x, " ")
		}

		// Sprawdz czy mrowka mogla zjesc jedzenie
		for i := range mrowka {
			for j := range jedzenie {
				if mrowka[i].powrot == 1 && (mrowka[i].x == jedzenie[j].x && mrowka[i].y == jedzenie[j].y && jedzenie[j].powrot == 1) {
					fmt.Printf("\u001b[32m\x1B[%d;%df%s\u001b[0m", mrowka[i].y, mrowka[i].x, "o")
				}
			}
		}

		// Sprawdz czy mrowka podniosla cokolwiek
		for i := range mrowka {
			if mrowka[i].powrot == 1 {
				i = i + 1
			} else {
				for j := range jedzenie {
					if mrowka[i].x == jedzenie[j].x && mrowka[i].y == jedzenie[j].y && jedzenie[j].powrot == 1 {
						mrowka[i].powrot = 1
						jedzenie[j].powrot = 0
					}
				}
			}
		}

		time.Sleep(time.Duration(config.opoznienie))

		// Poruszanie sie
		for i := range mrowka {
			mrowka[i].x += 1 - rand.Intn(3)

			if mrowka[i].x <= 1 {
				mrowka[i].x = 2
			}
			if mrowka[i].x > X-1 {
				mrowka[i].x = X - 1
			}

			mrowka[i].y += 1 - rand.Intn(3)

			if mrowka[i].y <= 1 {
				mrowka[i].y = 2
			}
			if mrowka[i].y > Y-1 {
				mrowka[i].y = Y - 1
			}
		}

		// Upuszczanie jedzenia przy mrowisku
		for i := range mrowka {
			if mrowka[i].powrot == 1 {
				for j := range gniazdo {
					if mrowka[i].x-1 == gniazdo[j].x && mrowka[i].y == gniazdo[j].y {
						temp := gen()
						gniazdo[temp].x = mrowka[i].x
						gniazdo[temp].y = mrowka[i].y
						gniazdo[temp].powrot = 1
						break
					} else if mrowka[i].x == gniazdo[j].x && mrowka[i].y-1 == gniazdo[j].y {
						temp := gen()
						gniazdo[temp].x = mrowka[i].x
						gniazdo[temp].y = mrowka[i].y
						gniazdo[temp].powrot = 1
						mrowka[i].powrot = 0
						break
					} else if mrowka[i].x+1 == gniazdo[j].x && mrowka[i].y == gniazdo[j].y {
						temp := gen()
						gniazdo[temp].x = mrowka[i].x
						gniazdo[temp].y = mrowka[i].y
						gniazdo[temp].powrot = 1
						mrowka[i].powrot = 0
						break
					} else if mrowka[i].x == gniazdo[j].x && mrowka[i].y+1 == gniazdo[j].y {
						temp := gen()
						gniazdo[temp].x = mrowka[i].x
						gniazdo[temp].y = mrowka[i].y
						gniazdo[temp].powrot = 1
						mrowka[i].powrot = 0
						break
					}
				}
			}
		}
	}

}

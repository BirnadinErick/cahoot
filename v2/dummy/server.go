package main

/*
#cgo CFLAGS: -g -Wall
#include <stdio.h>
#include <stdlib.h>
#include "lib.c"
*/
import "C"
import (
	"fmt"
	"log"
	"net/http"
	"strconv"
	"sync"
	"unsafe"
)

type User struct {
	Username string `json:"uname"`
	Score    int    `json:"score"`
}

var users []User
var usersLock sync.Mutex

// Handle the /score GET request
func scoreHandler(w http.ResponseWriter, r *http.Request) {
	// Parse query parameters
	quIDStr := r.URL.Query().Get("qu_id")
	ansStr := r.URL.Query().Get("ans_idx")

	if quIDStr == "" || ansStr == "" {
		http.Error(w, "Missing query parameters", http.StatusBadRequest)
		return
	}

	// Convert query parameters to integers
	quID, err := strconv.Atoi(quIDStr)
	if err != nil {
		http.Error(w, "Invalid qu_id parameter", http.StatusBadRequest)
		return
	}

	ans, err := strconv.Atoi(ansStr)
	if err != nil {
		http.Error(w, "Invalid ans parameter", http.StatusBadRequest)
		return
	}

	score := quID * ans

	// Return the score
	fmt.Fprint(w, score)
}

// Handle the /uname POST request
func unameHandler(w http.ResponseWriter, r *http.Request) {
	

	// Check if the method is POST
	if r.Method != http.MethodPost {
		http.Error(w, "Invalid request method", http.StatusMethodNotAllowed)
		return
	}
	

	err := r.ParseForm()
	if err != nil {
		http.Error(w, "Failed to parse form", http.StatusBadRequest)
		return
	}
	

	// Extract uname (username) and score from form data
	uname := r.FormValue("uname")
	scoreStr := r.FormValue("score")
	

	if uname == "" || scoreStr == "" {
		http.Error(w, "Missing uname or score", http.StatusBadRequest)
		return
	}
	

	score, err := strconv.Atoi(scoreStr)
	if err != nil {
		http.Error(w, "couldnot parse score", http.StatusBadRequest)
		return
	}
	

	user := User{Username: uname, Score: score}
	usersLock.Lock()
	users = append(users, user)
	usersLock.Unlock()

	if err := appendUserToFile(user); err != nil {
		http.Error(w, "Failed to write user to file", http.StatusInternalServerError)
		return
	}

	fmt.Write(w, 1)
}

// ja, the way we print scoreboard is not efficient, but for a project
// of our scope, I think this is ok. and computers are pretty fast
// regarding large arrays. the max players we are expecting is 32.
// so, instead of premature optimization, we just bruteforce
// the problem.
//
// Servus,
// BE.
func createUsersFile() error {
	usersLock.Lock()
	defer usersLock.Unlock()

	// Open the file with write and create mode, truncating existing content
	file, err := os.OpenFile("users.csv", os.O_WRONLY|os.O_CREATE|os.O_TRUNC, 0644)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := csv.NewWriter(file)
	defer writer.Flush()

	// Write CSV header
	if err := writer.Write([]string{"Username", "Score"}); err != nil {
		return err
	}

	// Write all current users
	for _, user := range users {
		if err := writer.Write([]string{user.Username, strconv.Itoa(user.Score)}); err != nil {
			return err
		}
	}

	return nil
}

func appendUserToFile(user User) error {
	file, err := os.OpenFile("users.csv", os.O_WRONLY|os.O_APPEND|os.O_CREATE, 0644)
	if err != nil {
		return err
	}
	defer file.Close()

	writer := csv.NewWriter(file)
	defer writer.Flush()

	// Append a single user entry
	return writer.Write([]string{user.Username, strconv.Itoa(user.Score)})
}

func main() {

	// test data; remove later dev;
	users = append(users, User{"alice", 90})
	users = append(users, User{"bob", 85})
	users = append(users, User{"carol", 78})

	// Create the initial file with existing users
	if err := createUsersFile(); err != nil {
		log.Fatalf("Failed to create users file: %v", err)
	}

	// endpoints 
	http.HandleFunc("/score", scoreHandler)
	http.HandleFunc("/uname", unameHandler)

	fmt.Println("starting...")
	log.Fatal(http.ListenAndServe(":8080", nil))
}

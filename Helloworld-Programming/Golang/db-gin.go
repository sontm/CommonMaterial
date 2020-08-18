package main

import "github.com/gin-gonic/gin"
//import "net/http"
//go get github.com/jinzhu/gorm
//go get github.com/gorilla/mux
//go get github.com/lib/pq
//go get github.com/rs/cors

import (
	"github.com/jinzhu/gorm"

	_ "github.com/jinzhu/gorm/dialects/postgres"
)

type Driver struct {
	gorm.Model
	Name    string
	License string
	Cars    []Car
}

type Car struct {
	gorm.Model
	Year      int
	Make      string
	ModelName string
	DriverID  int
}

var db *gorm.DB
var err error

var (
	drivers = []Driver{
		{Name: "Jimmy Johnson", License: "ABC123"},
		{Name: "Howard Hills", License: "XYZ789"},
		{Name: "Craig Colbin", License: "DEF333"},
	}
	cars = []Car{
		{Year: 2000, Make: "Toyota", ModelName: "Tundra", DriverID: 1},
		{Year: 2001, Make: "Honda", ModelName: "Accord", DriverID: 1},
		{Year: 2002, Make: "Nissan", ModelName: "Sentra", DriverID: 2},
		{Year: 2003, Make: "Ford", ModelName: "F-150", DriverID: 3},
	}
)

func main() {
	router := gin.Default()

	//db, err = gorm.Open("postgres", "host=db port=5432 user=postgres dbname=postgres sslmode=disable password=postgres")
	db, err = gorm.Open("postgres", "host=localhost port=5432 user=postgres dbname=postgres sslmode=disable password=123456")

	if err != nil {
		panic("failed to connect database")
	}

	defer db.Close()

	db.AutoMigrate(&Driver{})
	db.AutoMigrate(&Car{})

	
	// for index := range cars {
	// 	db.Create(&cars[index])
	// }

	// for index := range drivers {
	// 	db.Create(&drivers[index])
	// }

	router.GET("/cars", GetCars)
	router.GET("/drivers", GetDrivers)
	router.GET("/cars/:id", GetCar)
	router.GET("/drivers/:id", GetDriver)
	//router.HandleFunc("/cars/{id}", DeleteCar).Methods("DELETE")

	router.Run(":8081")
}

func GetCars(c *gin.Context) {
	var cars []Car
	db.Find(&cars)
	c.JSON(200, cars)
}

func GetCar(c *gin.Context) {
	id := c.Param("id")
	var car Car
	db.First(&car, id)
	c.JSON(200, car)
}

func GetDriver(c *gin.Context) {
	var driver Driver
	var cars []Car
	db.First(&driver, c.Param("id"))
	db.Model(&driver).Related(&cars)
	driver.Cars = cars

	c.JSON(200, driver)
}

func GetDrivers(c *gin.Context) {
	var cars []Driver
	db.Find(&cars)
	c.JSON(200, cars)
}

// func DeleteCar(w http.ResponseWriter, r *http.Request) {
// 	params := mux.Vars(r)
// 	var car Car
// 	db.First(&car, params["id"])
// 	db.Delete(&car)

// 	var cars []Car
// 	db.Find(&cars)
// 	json.NewEncoder(w).Encode(&cars)
// }

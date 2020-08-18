//go get -u github.com/gin-gonic/gin

package main

import "github.com/gin-gonic/gin"
import "net/http"

func main() {
	router := gin.Default()
	
	// Global middleware
	// Logger middleware will write the logs to gin.DefaultWriter even if you set with GIN_MODE=release.
	// By default gin.DefaultWriter = os.Stdout
	r.Use(gin.Logger())

	// Recovery middleware recovers from any panics and writes a 500 if there was one.
	r.Use(gin.Recovery())
	
	// router.GET("/someGet", getting)
	// router.POST("/somePost", posting)
	// router.PUT("/somePut", putting)
	// router.DELETE("/someDelete", deleting)
	// router.PATCH("/somePatch", patching)
	// router.HEAD("/someHead", head)
	// router.OPTIONS("/someOptions", options)

	router.GET("/ping", func(c *gin.Context) {
		c.JSON(200, gin.H{
			"message": "pong",
		})
	})

	// This handler will match /user/john but will not match /user/ or /user
	router.GET("/user/:name", func(c *gin.Context) {
		name := c.Param("name")
		c.String(http.StatusOK, "Hello %s", name)
	})

	// However, this one will match /user/john/ and also /user/john/send
	// If no other routers match /user/john, it will redirect to /user/john/
	router.GET("/user/:name/*action", func(c *gin.Context) {
		name := c.Param("name")
		action := c.Param("action")
		message := name + " is " + action
		c.String(http.StatusOK, message)
	})

	// Query string parameters are parsed using the existing underlying request object.
	// The request responds to a url matching:  /welcome?firstname=Jane&lastname=Doe
	router.GET("/welcome", func(c *gin.Context) {
		firstname := c.DefaultQuery("firstname", "Guest")
		lastname := c.Query("lastname") // shortcut for c.Request.URL.Query().Get("lastname")

		c.String(http.StatusOK, "Hello %s %s", firstname, lastname)
	})

	router.POST("/form_post", func(c *gin.Context) {
		message := c.PostForm("message")
		nick := c.DefaultPostForm("nick", "anonymous")

		c.JSON(200, gin.H{
			"status":  "posted",
			"message": message,
			"nick":    nick,
		})
	})

	//POST /post?id=1234&page=1 HTTP/1.1
	//name=manu&message=this_is_great
	// ==> id: 1234; page: 1; name: manu; message: this_is_great
	router.POST("/post", func(c *gin.Context) {

		id := c.Query("id")
		page := c.DefaultQuery("page", "0")
		name := c.PostForm("name")
		message := c.PostForm("message")

		fmt.Printf("id: %s; page: %s; name: %s; message: %s", id, page, name, message)
	})

	//POST /post?ids[a]=1234&ids[b]=hello HTTP/1.1
	//names[first]=thinkerou&names[second]=tianou
	// ==>ids: map[b:hello a:1234], names: map[second:tianou first:thinkerou]
	router.POST("/post", func(c *gin.Context) {

		ids := c.QueryMap("ids")
		names := c.PostFormMap("names")

		fmt.Printf("ids: %v; names: %v", ids, names)
	})






















	router.Run(":8081") // listen and serve on 0.0.0.0:8080 (for windows "localhost:8080")
}



package com.company;

import java.util.*;
import java.util.function.Consumer;
import java.util.stream.Collectors;
import java.util.stream.IntStream;
import java.util.stream.Stream;


public class Main {
    public static String getMyDefault() {
        System.out.println("Getting Default Value");
        return "Default Value";
    }

    public static void tryForEach() {
        //creating sample Collection
        List<Integer> myList = new ArrayList<Integer>();
        for(int i=0; i<4; i++) myList.add(i);

        //traversing using Iterator
        Iterator<Integer> it = myList.iterator();
        while(it.hasNext()){
            Integer i = it.next();
            System.out.println("Iterator Value::"+i);
        }

        //traversing through forEach method of Iterable with anonymous class
        myList.forEach(new Consumer<Integer>() {

            public void accept(Integer t) {
                System.out.println("forEach anonymous class Value::"+t);
            }

        });

        //traversing with Consumer interface implementation
        MyConsumer action = new MyConsumer();
        myList.forEach(action);

        // With Index in Foreach
        IntStream.range(0, myList.size())
                .forEach(idx ->
                        System.out.println("forEach Lambda class Value::"+idx + "-" + myList.get(idx))
                )
        ;

    }
    public static void tryLambda() {
        List<String> list=new ArrayList<String>();
        list.add("A");
        list.add("B");
        list.add("C");
        list.add("D");
        list.forEach(
                (names)->{
                    System.out.println(names + " ");
                }
        );


        //with lambda
        Drawable d2=(w)->{
            System.out.println("Drawing "+w);
        };
        d2.draw(4);



        //Thread Example with lambda
        Runnable r2=()->{
            System.out.println("Thread2 is running...");
        };
        Thread t2=new Thread(r2);
        t2.start();

        Stream<String> filtered_data = list.stream().filter(p -> p == "A");
        filtered_data.forEach(
                p -> System.out.println("Filtered:" + p)
        );
    }
    public static void tryMethodReference() {
        System.out.println("Hello, this is static method.");
    }
    //https://www.baeldung.com/java-optional
    //https://dzone.com/articles/using-optional-correctly-is-not-optional
    //The intent of Java when releasing Optional was to use it as a return type
    //  Not as parameter, because we need checknulll
    //using Optional in a serializable class will result in a NotSerializableException
    public static void tryOptional() {
        Optional<String> checkNull = Optional.ofNullable("aa");
        // Before
//        if(name != null) {
//            System.out.println(name.length());
//        }

        checkNull.ifPresent(System.out::println);   // printing value by using method reference
        checkNull.ifPresent(s -> System.out.println(s));

        System.out.println(checkNull.map(String::toLowerCase));

        System.out.println(checkNull.orElse("Default Value"));
        System.out.println(checkNull.orElseGet(() -> "Default Value"));

        // or return Optional.empty
        System.out.println(checkNull.filter(s -> s.equals("aa")));

        //the argument passed to the of() method can't be null. Otherwise, we'll get a NullPointerException:
        //   use ofNullable instead
        String nullName = null;
        String name = Optional.ofNullable(nullName).orElse("john");
        String name2 = Optional.ofNullable(nullName).orElseGet(() -> "john");


        String text = "Text present";
        //orElseGet() , the getMyDefault() method is not even invoked since the contained value is present.
        //orElse(), whether the wrapped value is present or not, the default object is created.
        // So in this case, we have just created one redundant object that is never used.
        String defaultText = Optional.ofNullable(text).orElseGet(Main::getMyDefault);
        defaultText = Optional.ofNullable(text).orElse(getMyDefault());


        String ex = Optional.ofNullable(text).orElseThrow(IllegalArgumentException::new);


        //get() can only return a value if the wrapped object is not null; otherwise, it throws a no such element exception:

        //We can run an inline test on our wrapped value with the filter method.
        // It takes a predicate as an argument and returns an Optional object.
        Integer year = 2016;
        Optional<Integer> yearOptional = Optional.of(year);
        boolean is2016 = yearOptional.filter(y -> y == 2016).isPresent();

        // Filter and Map
        boolean a = Optional.ofNullable(new Modem(12.0))
                .map(Modem::getPrice)
                .filter(p -> p >= 10)
                .filter(p -> p <= 15)
                .isPresent();


        List<String> companyNames = Arrays.asList(
                "paypal", "oracle", "", "microsoft", "", "apple");
        Optional<List<String>> listOptional = Optional.of(companyNames);
        int size = listOptional
                .map(List::size)
                .orElse(0);


        //flatMap takes a wrapped value and unwraps it before transforming it.
        Person person = new Person("john", 26);
        Optional<Person> personOptional = Optional.of(person);

        Optional<Optional<String>> nameOptionalWrapper
                = personOptional.map(Person::getName);
        Optional<String> nameOptional
                = nameOptionalWrapper.orElseThrow(IllegalArgumentException::new);
        String name1 = nameOptional.orElse("");

        String SIMPLEFLATMAP = personOptional
                .flatMap(Person::getName)
                .orElse("");
    }


    public static void tryCollectors() {
        List<Product> productsList = new ArrayList<Product>();
        //Adding Products
        productsList.add(new Product(1,"HP Laptop",25000f));
        productsList.add(new Product(2,"Dell Laptop",30000f));
        productsList.add(new Product(3,"Lenevo Laptop",28000f));
        productsList.add(new Product(4,"Sony Laptop",28000f));
        productsList.add(new Product(5,"Apple Laptop",90000f));

        // Summing
        Double sumPrices =
                productsList.stream()
                        .collect(Collectors.summingDouble(x->x.price));  // collecting as list
        System.out.println("Sum of prices: "+sumPrices);

        // Couting
        Long noOfElements = productsList.stream()
                .collect(Collectors.counting());
        System.out.println("Total elements : "+noOfElements);

    }
    //https://www.javatpoint.com/java-8-stream-filter
    public static void tryStreaming() {
        List<Product> productsList = new ArrayList<Product>();
        //Adding Products
        productsList.add(new Product(1,"HP Laptop",25000f));
        productsList.add(new Product(2,"Dell Laptop",30000f));
        productsList.add(new Product(3,"Lenevo Laptop",28000f));
        productsList.add(new Product(4,"Sony Laptop",28000f));
        productsList.add(new Product(5,"Apple Laptop",90000f));
        List<Float> productPriceList2 =productsList.stream()
                .filter(p -> p.price > 30000)// filtering data
                .map(p->p.price)        // fetching price
                .collect(Collectors.toList()); // collecting as list
        System.out.println(productPriceList2);


        productsList.stream()
                .filter(product -> product.price == 30000)
                .forEach(product -> System.out.println(product.name));

        // reduce: This method takes a sequence of input elements and combines them into a single summary result
        // by repeated operation. For example, finding the sum of numbers, or accumulating elements into a list.
        Float totalPrice = productsList.stream()
                .map(product->product.price)
                .reduce(0.0f,(sum, price)->sum+price);   // accumulating price
        System.out.println(totalPrice);


        // max, min
        Product productA = productsList.stream()
                .max((product1, product2)->
                        product1.price > product2.price ? 1: -1).get();

        long count = productsList.stream()
                .filter(product->product.price<30000)
                .count();
    }






    public static void main(String[] args) {
	// write your code here
        tryForEach();

        tryLambda();

        Sayable sayable = Main::tryMethodReference;
        sayable.say();

        tryCollectors();

        tryStreaming();


    }
}

@FunctionalInterface
interface Sayable{
    void say();
}

//An Interface that contains exactly one abstract method is known as functional interface.
@FunctionalInterface
interface Drawable{
    public void draw(int w);
}

class MyConsumer implements Consumer<Integer> {

    public void accept(Integer t) {
        System.out.println("Consumer impl Value::"+t);
    }
}

class Modem {
    private Double price;

    public Modem(Double price) {
        this.price = price;
    }
    // standard getters and setters
    public Double getPrice(){return price;}
}

class Person {
    private String name;
    private int age;
    private String password;
    public Person(String n, int a) {
        name = n; age = a;
    }
    public Optional<String> getName() {
        return Optional.ofNullable(name);
    }

    public Optional<Integer> getAge() {
        return Optional.ofNullable(age);
    }

    public Optional<String> getPassword() {
        return Optional.ofNullable(password);
    }

    // normal constructors and setters
}

class Product{
    int id;
    String name;
    float price;

    public Product(int id, String name, float price) {
        this.id = id;
        this.name = name;
        this.price = price;
    }
}


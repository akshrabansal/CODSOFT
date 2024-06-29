import java.util.HashMap;
import java.util.Map;
import java.util.Random;
import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class ChatBot {

    private static Map<String, String[]> intents;

    public static void main(String[] args) {
        // Define intents and responses
        initializeIntents();

        System.out.println("GO! Bot is running!");
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.print("You: ");
            String message = scanner.nextLine().toLowerCase();

            if (message.contains("bye") || message.contains("exit")) {
                System.out.println("Bot: Goodbye!");
                break;
            }

            String intent = predictIntent(message);
            String response = generateResponse(intent);
            System.out.println("Bot: " + response);
        }

        scanner.close();
    }

    private static void initializeIntents() {
        intents = new HashMap<>();
        intents.put("greeting", new String[]{"Hello!", "Hi there!", "Greetings!"});
        intents.put("howareyou", new String[]{"I'm just a bunch of code, but I'm doing great!", "Functioning as expected!"});
        intents.put("name", new String[]{"I am a simple chatbot created in Java.", "You can call me JavaBot."});
        intents.put("goodbye", new String[]{"Goodbye!", "See you later!", "Have a great day!"});
        intents.put("weather", new String[]{"The weather is fine.", "It's sunny today!", "It looks like it might rain."});
        intents.put("time", new String[]{"I don't have a clock, but it's time to code!", "Time is an illusion."});
        // Add more intents and responses as needed
    }

    private static String predictIntent(String message) {
        if (matchPattern(message, ".*\\bhello\\b.*|.*\\bhi\\b.*|.*\\bhey\\b.*")) {
            return "greeting";
        } else if (matchPattern(message, ".*\\bhow are you\\b.*")) {
            return "howareyou";
        } else if (matchPattern(message, ".*\\bwhat is your name\\b.*|.*\\bwho are you\\b.*")) {
            return "name";
        } else if (matchPattern(message, ".*\\bbye\\b.*|.*\\bexit\\b.*")) {
            return "goodbye";
        } else if (matchPattern(message, ".*\\bweather\\b.*")) {
            return "weather";
        } else if (matchPattern(message, ".*\\btime\\b.*")) {
            return "time";
        } else {
            return "unknown";
        }
    }

    private static boolean matchPattern(String message, String pattern) {
        Pattern p = Pattern.compile(pattern);
        Matcher m = p.matcher(message);
        return m.matches();
    }

    private static String generateResponse(String intent) {
        Random rand = new Random();
        String[] responses = intents.get(intent);

        if (responses != null) {
            return responses[rand.nextInt(responses.length)];
        } else {
            return "I'm sorry, I don't understand that. Can you rephrase?";
        }
    }
}

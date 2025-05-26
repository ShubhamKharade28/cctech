using System.Text.Json;

string[] shoppingList = [];
string dataFile = "shoppingList.json";

if (File.Exists(dataFile))
{
    string json = File.ReadAllText(dataFile);
    shoppingList = JsonSerializer.Deserialize<string[]>(json) ?? [];
}

void saveShoppingList()
{
    string json = JsonSerializer.Serialize(shoppingList);
    File.WriteAllText(dataFile, json);
}

void printShoppingList()
{
    if (shoppingList.Length == 0)
    {
        Console.WriteLine("The list is empty");
        return;
    }

    Console.WriteLine("Items:");
    for(int i=0; i<shoppingList.Length; i++)
    {
        string item = shoppingList[i];
        Console.WriteLine($"\t{i+1}. {item}");
    }
}

void inputAndAddItem()
{
    Console.Write("Enter item to add: ");
    string? newItem = Console.ReadLine();
    if (!string.IsNullOrEmpty(newItem))
    {
        shoppingList = [.. shoppingList, newItem];
        Console.WriteLine($"\"{newItem}\" added.");
    }
    saveShoppingList();
}

void inputAndRemoveItem()
{
    if (shoppingList.Length == 0)
    {
        Console.WriteLine("List is empty! Nothing to remove.");
        return;
    }

    printShoppingList();
    Console.WriteLine("Enter item number to remove: ");
    string? input = Console.ReadLine();

    if (int.TryParse(input, out int index))
    {
        index--;
        if (index >= 0 && index < shoppingList.Length)
        {
            string removedItem = shoppingList[index];
            shoppingList = [.. shoppingList[..index], .. shoppingList[(index + 1)..]];
            Console.WriteLine($"Removed \"{removedItem}\".");
        }
        else
        {
            Console.WriteLine("Invalid item number.");
        }
    }
    else
    {
        Console.WriteLine("Invalid input.");
    }
}

while (true)
{
    Console.WriteLine("\nShopping List");
    Console.WriteLine("1. View List");
    Console.WriteLine("2. Add Item");
    Console.WriteLine("3. Remove Item");
    Console.WriteLine("4. Exit");
    Console.Write("Choose an option (1-4): ");

    string? input = Console.ReadLine();
    Console.WriteLine();

    if (input == "1") printShoppingList();
    else if (input == "2") inputAndAddItem();
    else if (input == "3") inputAndRemoveItem();
    else if (input == "4")
    {
        Console.WriteLine("Goodbye!");
        break;
    }
    else
    {
        Console.WriteLine("Invalid choice.");
    }
}
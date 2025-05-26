
using System.Text.Json;

public class ShoppingList
{
    private string[] items = [];
    private readonly string filePath;

    public ShoppingList(string filePath)
    {
        this.filePath = filePath;
        Load();
    }

    public void Print()
    {
        if (items.Length == 0)
        {
            Console.WriteLine("The list is empty");
            return;
        }

        Console.WriteLine("Items:");
        for (int i = 0; i < items.Length; i++)
        {
            string item = items[i];
            Console.WriteLine($"\t{i + 1}. {item}");
        }
    }

    public void AddItem(string item)
    {
        items = [.. items, item];
        Console.WriteLine($"{item} added");
        Save();
    }

    public void Load()
    {
        if (File.Exists(filePath))
        {
            string json = File.ReadAllText(filePath);
            items = JsonSerializer.Deserialize<string[]>(json) ?? [];
        }
    }
    public void Save()
    {
        string json = JsonSerializer.Serialize(items);
        File.WriteAllText(filePath, json);
    }
}
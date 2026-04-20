using Silk.NET.Input;
using Silk.NET.Maths;
using Silk.NET.Windowing;

namespace LearningSilkNet;

public class Program
{
    public static void Main(string[] args)
    {
        var app = new App();
        app.Initialize();
    }
}

public class App
{
    private IWindow _window;
    private IInputContext _input;

    public App()
    {

    }

    public void Initialize()
    {
        CreateWindow();
    }

    public void CreateWindow()
    {
        var windowOptions = WindowOptions.Default with
        {
            Size = new Vector2D<int>(800, 600),
            Title = "My first Silk.NET application",
        };

        _window = Window.Create(windowOptions);

        _window.Load += OnLoad;
        _window.Update += OnUpdate;
        _window.Render += OnRender;

        _window?.Run();
    }

    private void OnLoad()
    {
        _input = _window.CreateInput();
        foreach (var keyboard in _input.Keyboards)
        {
            keyboard.KeyDown += OnKeyDown;
        }
    }

    private void OnUpdate(double dt)
    {

    }

    private void OnRender(double dt)
    {

    }

    private void OnKeyDown(IKeyboard keyboard, Key key, int keyCode)
    {
        if (key == Key.Escape)
        {
            _window.Close();
        }
    }
}

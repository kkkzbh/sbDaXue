
using UnityEngine;
using UnityEngine.SceneManagement;

public class GameManager : MonoBehaviour
{
    public static GameManager Instance { get; private set; }

    public int world { get; private set; }
    public int stage { get; private set; }
    public int lifes { get; private set; }
    
    public int coins { get; private set; }
    
    private void Awake()
    {
        if (Instance is not null) {
            DestroyImmediate(gameObject);
        } else {
            Instance = this;
            DontDestroyOnLoad(gameObject);
        }
    }
    
    private void OnDestroy()
    {
        if (Instance == this) {
            Instance = null;
        }
    }
    
    private void Start()
    {
        Application.targetFrameRate = 120;
        NewGame();
    }

    public void NewGame()
    {
        lifes = 3;
        coins = 0;
        LoadLevel(1,1);
    }

    public void NextLevel()
    {
        LoadLevel(world,stage + 1);
    }

    public void ResetLevel()
    {
        LoadLevel(world,stage);
    }

    public void ResetLevel(float delay)
    {
        Invoke(nameof(ResetLevel),delay);
    }

    public void LoadLevel(int world, int stage)
    {
        this.world = world;
        this.stage = stage;
        SceneManager.LoadScene($"{world}-{stage}");
    }

    public void GameOver()
    {
        NewGame();
    }

    public void AddCoin()
    {
        ++coins;
        if (coins == 100) {
            AddLife();
            coins = 0;
        }
    }

    public void AddLife()
    {
        ++lifes;
    }
    
}

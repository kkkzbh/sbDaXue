using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using std;
using TMPro;
using UnityEngine.SceneManagement;

public class Manage : MonoBehaviour
{

    public GameObject airBarrier;
    public GameObject barrier;
    public GameObject grass;
    public GameObject home;
    public GameObject river;
    public GameObject wall;
    
    public GameObject bullet;
    public GameObject enemyBullet;
    public GameObject player;
    public GameObject[] enemy;
    
    public GameObject bornEffect;
    public GameObject explodeEffect;
    public GameObject defendEffect;

    private HashSet<Vector3> _set = new HashSet<Vector3>()
    {
        new Vector3(0,-8),
        new Vector3(-1,-8),
        new Vector3(-1,-7),
        new Vector3(0,-7),
        new Vector3(1,7),
        new Vector3(1,-8),
        new Vector3(-2,-8),
    };

    private const float PlayerReactivationTime = 2.5f;
    private const float EnemyReactivationTime = 5.0f;
    private const int DefaultEnemyCount = 8;
    private const float ReturnInterVal = 3.5f;

    private const int MaxPlayerHp = 5;
    private int _hp = MaxPlayerHp;
    private int _scores = 0;

    public TextMeshProUGUI hpText;
    public TextMeshProUGUI scoresText;
    public GameObject defeatUI;
    private void Awake()
    {
        InitMap();

        hpText.text = _hp.ToString();
        scoresText.text = _scores.ToString();
    }

    private void InitMap()
    {
        CreatHome();
        CreatAirBarrier();
        CreateOthers();
        CreatePlayer();
        var v = enemy[0].GetComponent<Enemy>();
        foreach (var pos in v.bornPos)
        {
            _set.Add(pos);
        }

        for (int i = 0; i != DefaultEnemyCount; ++i)
        {
            int num = Random.Range(0, 100);
            if (num < 50)
            {
                CreateEnemy(Enemy.Kind.Enemy);
            }
            else
            {
                CreateEnemy(Enemy.Kind.SEnemy);
            }
        }
    }

    private void CreatePlayer()
    {
        var v = player.GetComponent<IBorn>();
        v.Born();
    }

    private void CreateEnemy(Enemy.Kind k)
    {
        var v = enemy[(int)k].GetComponent<IBorn>();
        v.Born();
    }

    public void BornPlayer()
    {
        hpText.text = (--_hp).ToString();
        if (_hp == 0)
        {
            Instantiate(explodeEffect, transform.position, Quaternion.identity);
            Defeat();
        }
        else
        {
            Invoke(nameof(CreatePlayer), PlayerReactivationTime);
        }
    }

    public void Defeat()
    {
        defeatUI.SetActive(true);
        StartCoroutine(CReturnOption());
    }

    private IEnumerator CReturnOption()
    {
        yield return new WaitForSeconds(ReturnInterVal);
        var option = SceneManager.LoadSceneAsync("Main");
        yield return option;
    }

    private IEnumerator CBornEnemy(Enemy.Kind k)
    {
        yield return new WaitForSeconds(EnemyReactivationTime);
        CreateEnemy(k);
    }

    public void BornEnemy(Enemy.Kind k)
    {
        scoresText.text = (++_scores).ToString();
        StartCoroutine(CBornEnemy(k));
    }

    private Vector3 CreatePos(int flo,int cei)
    {
        while (true)
        {
            var v = new Vector3(Random.Range(flo, cei), Random.Range(flo, cei));
            if (_set.Add(v))
            {
                return v;
            }
        }
    }

    private void CreateOthers()
    {
        CreateItem(wall,70,-8,9);
        CreateItem(barrier,30,-8,9);
        CreateItem(grass,20,-8,9);
        CreateItem(river,15,-8,9);
    }

    private void CreateItem(GameObject item, int n, int flo, int cei)
    {
        for (int i = 0; i != n; ++i)
        {
            New(item, CreatePos(flo, cei));
        }
    }

    private void CreatHome()
    {
        New(home,new Vector3(0,-7.983f,0));
        New(wall,new Vector3(-1.03f,-7.983f,0));
        New(wall,new Vector3(-1.03f,-6.983f,0));
        New(wall,new Vector3(-0.03f,-6.983f,0));
        New(wall,new Vector3(0.97f,-6.983f,0));
        New(wall,new Vector3(0.97f,-7.983f,0));
    }

    private void CreatAirBarrier()
    {
        // left right
        for (int y = -9; y <= 9; ++y)
        {
            New(airBarrier, new Vector3(-11.15f, y, 0));
            New(airBarrier, new Vector3(11.15f, y, 0));
        }
        // down up
        for (int x = -11; x <= 11; ++x)
        {
            New(airBarrier, new Vector3(x, -9, 0));
            New(airBarrier, new Vector3(x, 9, 0));

        }
    }
    
    private GameObject New(GameObject item, Vector3 pos, Quaternion rotation = default)
    {
        return Instantiate(item, pos, rotation, transform);  
    }

}

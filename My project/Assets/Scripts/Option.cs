

using System.Collections;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Option : MonoBehaviour
{

    private int _choice = 1;
    public Transform playOne;
    public Transform playTwo;
    
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        var v = Input.GetAxisRaw("Vertical");
        if (v > 0)
        {
            _choice = 1;
            transform.position = playOne.position;
        }
        else if (v < 0)
        {
            _choice = 2;
            transform.position = playTwo.position;
        }

        if (Input.GetKeyDown(KeyCode.Space) || Input.GetKeyDown(KeyCode.Return))
        {
            if (_choice == 1)
            {
                StartCoroutine(CLoadScene("GameScene"));
            }
        }
    }

    private IEnumerator CLoadScene(string scene)
    {
        AsyncOperation operation = SceneManager.LoadSceneAsync(scene);
        yield return operation;
    }
}

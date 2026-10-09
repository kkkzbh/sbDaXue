

using System.Collections;
using UnityEngine;

public class FlagPole : MonoBehaviour
{
    public Transform flag;
    public Transform poloBottom;
    public Transform castle;
    public float speed = 6f;

    public int nextWorld;
    public int nextStage;

    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.CompareTag("Player")) {
            StartCoroutine(MoveTo(flag, poloBottom.position));
            StartCoroutine(LevelCompleteSequence(other.transform));
        }
    }

    private IEnumerator LevelCompleteSequence(Transform mario)
    {
        mario.GetComponent<PlayerMovement>().enabled = false;
        
        yield return MoveTo(mario.transform, poloBottom.position);
        yield return MoveTo(mario.transform, mario.transform.position + Vector3.right);
        yield return MoveTo(mario.transform, mario.transform.position + Vector3.right + Vector3.down);
        yield return MoveTo(mario.transform, castle.position);

        mario.gameObject.SetActive(false);

        yield return new WaitForSeconds(2f);

        GameManager.Instance.LoadLevel(nextWorld, nextStage);
    }
    
    private IEnumerator MoveTo(Transform subject, Vector3 position)
    {
        while (Vector3.Distance(subject.position, position) > 0.125f)
        {
            subject.position = Vector3.MoveTowards(subject.position, position, speed * Time.deltaTime);
            yield return null;
        }

        subject.position = position;
    }
}

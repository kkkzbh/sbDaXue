
using System;
using System.Collections;
using UnityEngine;

public class CPipe : MonoBehaviour
{

    public Transform connection;
    
    public String enterRaw;
    public bool reverse;
    public Vector3 enterDirction;
    public Vector3 exitDirction = Vector3.zero;
    private void OnTriggerStay2D(Collider2D other)
    {
        if (other.CompareTag("Player")) {
            if (Input.GetAxis(enterRaw) * (reverse ? -1f : 1f) > 0.01f) {
                StartCoroutine(Enter(other.transform));
            }
        }    
    }

    private IEnumerator Enter(Transform mario)
    {
        mario.GetComponent<PlayerMovement>().enabled = false;

        Vector3 enteredPosition = transform.position + enterDirction;
        Vector3 enteredScale = Vector3.one * 0.9f;

        yield return Move(mario, enteredPosition, enteredScale);
        
        Camera.main.GetComponent<SideScrolling>().SetUnderground(connection.position.y < 0f);

        if (exitDirction != Vector3.zero) {
            mario.position = connection.position - exitDirction;
            yield return Move(mario, connection.position + exitDirction, Vector3.one);
        } else {
            mario.position = connection.position;
            mario.localScale = Vector3.one;
        }

        mario.GetComponent<PlayerMovement>().enabled = true;
    }

    private IEnumerator Move(Transform mario, Vector3 endPosition,Vector3 endScale)
    {
        float elapsed = 0f,duration = 2f;
        Vector3 startPosition = mario.position;
        Vector3 startScale = mario.localScale;
        while (elapsed < duration) {
            float t = elapsed / duration;
            mario.position = Vector3.Lerp(startPosition, endPosition, t);
            mario.localScale = Vector3.Lerp(startScale, endScale, t);
            elapsed += Time.deltaTime;
            yield return null;
        }

        mario.position = endPosition;
        mario.localScale = endScale;
    }
    
}

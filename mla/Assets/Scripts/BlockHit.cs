
using System;
using System.Collections;
using UnityEngine;

public class BlockHit : MonoBehaviour
{
    public Sprite emptyBlock;
    public int maxHits = -1;
    public bool hidden;

    public GameObject hitItem;
    
    private bool animating;

    private SpriteRenderer spriteRenderer;
    private new BoxCollider2D collider;
    
    private void Awake()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
        collider = GetComponent<BoxCollider2D>();
        if (hidden) {
            spriteRenderer.enabled = false;
            collider.isTrigger = true;
            gameObject.layer = LayerMask.NameToLayer("Ignore Raycast");
        }
    }

    private void OnCollisionEnter2D(Collision2D other)
    {
        if (!animating && maxHits != 0 && other.gameObject.CompareTag("Player")) {
            if (transform.DotTest(other.transform, Vector2.down)) {
                Hit();
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D other)
    {
        if (maxHits != 0 && other.gameObject.CompareTag("Player")) {
            if (transform.DotTest(other.transform, Vector2.down)) {
                Hit();
            }
        }
    }

    private void Hit()
    {
        if (hidden) {
            spriteRenderer.enabled = true;
            collider.isTrigger = false;
            gameObject.layer = LayerMask.NameToLayer("Default");
        }

        if (--maxHits == 0) {
            spriteRenderer.sprite = emptyBlock;
        }

        StartCoroutine(Animate());

        if (hitItem != null) {
            Instantiate(hitItem, transform.position, Quaternion.identity);
        }
        
    }

    private IEnumerator Animate()
    {
        animating = true;

        Vector3 restingPosition = transform.localPosition;
        Vector3 animatedPosition = restingPosition + Vector3.up * 0.5f;

        yield return Move(restingPosition, animatedPosition);
        yield return Move(animatedPosition, restingPosition);

        animating = false;
    }

    private IEnumerator Move(Vector3 from, Vector3 to)
    {
        float elapsed = 0f;
        float duration = 0.125f;

        while (elapsed < duration) {
            float t = elapsed / duration;

            transform.localPosition = Vector3.Lerp(from, to, t);
            elapsed += Time.deltaTime;

            yield return null;
        }

        transform.localPosition = to;

    }
    
}

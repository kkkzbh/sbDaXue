
using UnityEngine;

public class Koopa : MonoBehaviour
{
    public Sprite shellSprite;
    public float shellSpeed = 12f;
    
    private bool shelled;
    private bool pushed;
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("Player")) {
            Player player = collision.gameObject.GetComponent<Player>();
            if (transform.DotTest(collision.transform, Vector2.up)) {
                EnterShell();
            } else {
                player.Hit();
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.CompareTag("Player")) {
            if (collision.gameObject.GetComponent<Player>().starPower) {
                Hit();
            } else if (!shelled) {
                return;
            } else if (pushed) {
                Player player = collision.GetComponent<Player>();
                player.Hit();
            } else {
                Vector2 dirction = (new Vector2(transform.position.x - collision.transform.position.x, 0f)).normalized;
                PushShell(dirction);
            }
        } else if (!shelled && collision.gameObject.layer == LayerMask.NameToLayer("Shell")) {
            Hit();
        }

    }

    private void EnterShell()
    {
        shelled = true;
        GetComponent<AnimatedScript>().enabled = false;
        GetComponent<EntityMovement>().enabled = false;
        GetComponent<SpriteRenderer>().sprite = shellSprite;
    }

    private void PushShell(Vector2 dirction)
    {
        pushed = true;
        gameObject.layer = LayerMask.NameToLayer("Shell");
        
        EntityMovement movement = GetComponent<EntityMovement>();
        movement.dirction = dirction;
        movement.speed = shellSpeed;
        movement.enabled = true;

    }
    
    private void Hit()
    {
        GetComponent<AnimatedScript>().enabled = false;
        GetComponent<DeathAnimation>().enabled = true;
        Destroy(gameObject,3f);
    }

    private void OnBecameInvisible()
    {
        if (pushed) {
            Destroy(gameObject);
        }
    }
}
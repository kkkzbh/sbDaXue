

using UnityEngine;

public class Goomba : MonoBehaviour
{
    public Sprite flatSprite;
    
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.CompareTag("Player")) {
            Player player = collision.gameObject.GetComponent<Player>();
            if (transform.DotTest(collision.transform, Vector2.up)) {
                Flatten();
            } else {
                player.Hit();
            }
        }
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        if (collision.gameObject.layer == LayerMask.NameToLayer("Shell")) {
            Hit();
        } else if (collision.CompareTag("Player") && collision.gameObject.GetComponent<Player>().starPower) {
            Hit();
        } 
    }

    private void Flatten()
    {
        GetComponent<CircleCollider2D>().enabled = false;
        GetComponent<AnimatedScript>().enabled = false;
        GetComponent<EntityMovement>().enabled = false;
        GetComponent<SpriteRenderer>().sprite = flatSprite;
        Destroy(gameObject,0.5f);
    }

    private void Hit()
    {
        GetComponent<AnimatedScript>().enabled = false;
        GetComponent<DeathAnimation>().enabled = true;
        Destroy(gameObject,3f);
    }
    
}

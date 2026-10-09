
using UnityEngine;
using std;
public class Bullet : MonoBehaviour
{
    
    public float moveSpeed = 10.0f;

    public AudioClip hitAdc;
    public enum Kind
    {
        Player,
        Enemy,
        
    }
    
    public Kind kind;
    // Start is called before the first frame update
    void Start()
    {
        
    }

    // Update is called once per frame
    void Update()
    {
        transform.Translate(Vector3.up * moveSpeed * Time.deltaTime);
    }

    private void OnTriggerEnter2D(Collider2D collision)
    {
        switch (collision.tag)
        {
            case "Tank":
                //collision.SendMessage("Die");
                if (kind != Kind.Player)
                {
                    collision.gameObject.GetComponent<IDeath>().Die();
                    Destroy(gameObject);
                }
                break;
            case "Heart":
                //collision.SendMessage("Die");
                collision.gameObject.GetComponent<IDeath>().Die();
                Destroy(gameObject);
                break;
            case "Barrier":
                if (kind == Kind.Player)
                {
                    AudioSource.PlayClipAtPoint(hitAdc, collision.transform.position);
                }

                Destroy(gameObject);
                break;
            case "Wall":
                if (kind == Kind.Player)
                {
                    AudioSource.PlayClipAtPoint(hitAdc, collision.transform.position);
                }

                Destroy(collision.gameObject);
                Destroy(gameObject);
                break;
            case "Enemy":
                if (kind != Kind.Enemy)
                {
                    collision.gameObject.GetComponent<IDeath>().Die();
                    Destroy(gameObject);
                }
                break;
        };
    }
}

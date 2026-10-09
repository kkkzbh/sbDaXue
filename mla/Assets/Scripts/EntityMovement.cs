
using System;
using UnityEngine;

public class EntityMovement : MonoBehaviour
{

    public float speed = 2f;
    public Vector2 dirction = Vector2.left;

    private new Rigidbody2D rigidbody;
    
    private Vector2 velocity;

    private void Awake()
    {
        rigidbody = GetComponent<Rigidbody2D>();
        enabled = false;
    }

    private void OnBecameVisible()
    {
        enabled = true;
    }

    private void OnBecameInvisible()
    {
        enabled = false;
    }

    private void OnEnable()
    {
        rigidbody.WakeUp();
    }

    private void OnDisable()
    {
        velocity = Vector2.zero;
        rigidbody.Sleep();
    }

    private void FixedUpdate()
    {
        
        velocity.x = speed * dirction.x;
        velocity.y += Physics2D.gravity.y * Time.fixedDeltaTime;
        
        rigidbody.MovePosition(rigidbody.position + velocity * Time.fixedDeltaTime);

        if (rigidbody.Raycast(dirction)) {
            dirction = -dirction;
        }

        if (rigidbody.Raycast(Vector2.down)) {
            velocity.y = Mathf.Max(velocity.y, 0f);
        }

        if (dirction.x > 0f) {
            transform.localEulerAngles = new Vector3(0, 180, 0);
        } else if (dirction.x < 0f) {
            transform.localEulerAngles = Vector3.zero;
        }
        
    }
    
}

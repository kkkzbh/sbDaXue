

using UnityEngine;

public class AnimatedScript : MonoBehaviour
{
    public Sprite[] sprites;
    public float framerate = 1f / 6f;
    
    private SpriteRenderer spriteRenderer;
    private int frame;
    
    private void Awake()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
    }

    private void OnEnable()
    {
        frame = 0;
        InvokeRepeating(nameof(Animate),framerate,framerate);
    }

    private void OnDisable()
    {
        CancelInvoke();
    }

    private void Animate()
    {
        ++frame;
        if (frame == sprites.Length) {
            frame = 0;
        }
    
        spriteRenderer.sprite = sprites[frame];
    }
    
}

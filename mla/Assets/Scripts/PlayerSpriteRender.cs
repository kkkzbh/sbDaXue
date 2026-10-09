

using UnityEngine;

public class PlayerSpriteRender : MonoBehaviour
{
    public SpriteRenderer spriteRenderer { get; private set; }
    private PlayerMovement playerMovement;

    public Sprite idle;
    public Sprite jump;
    public AnimatedScript run;
    public Sprite slide;
    
    private void Awake()
    {
        spriteRenderer = GetComponent<SpriteRenderer>();
        playerMovement = GetComponentInParent<PlayerMovement>();
    }

    private void OnEnable()
    {
        spriteRenderer.enabled = true;
    }

    private void OnDisable()
    {
        spriteRenderer.enabled = false;
        run.enabled = false;
    }

    private void LateUpdate()
    {
        run.enabled = playerMovement.running;
        
        if (playerMovement.jumping) {
            spriteRenderer.sprite = jump;
        } else if (playerMovement.sliding) {
            spriteRenderer.sprite = slide;
        } else if(!playerMovement.running) {
            spriteRenderer.sprite = idle;
        }
    }
    
}

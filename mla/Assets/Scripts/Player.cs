
using System.Collections;
using UnityEngine;


public class Player : MonoBehaviour
{
    public PlayerSpriteRender smallRenderer;
    public PlayerSpriteRender bigRenderer;
    private PlayerSpriteRender activeRender;

    private DeathAnimation deathAnimation;
    private CapsuleCollider2D capsuleCollider2D;

    public bool small => smallRenderer.enabled;
    public bool big => bigRenderer.enabled;
    public bool dead => deathAnimation.enabled;
    public bool starPower { get; private set;  }

    private void Awake()
    {
        deathAnimation = GetComponent<DeathAnimation>();
        capsuleCollider2D = GetComponent<CapsuleCollider2D>();
        activeRender = smallRenderer;

    }

    public void Hit()
    {
        if (starPower || dead) {
            return;
        }
        if (big) {
            Shrink();    
        } else {
            Death();            
        }
    }
    
    private void Death()
    {
        smallRenderer.enabled = false;
        bigRenderer.enabled = false;
        deathAnimation.enabled = true;

        GameManager.Instance.ResetLevel(3f);

    }
    
    private void Shrink()
    {
        smallRenderer.enabled = true;
        bigRenderer.enabled = false;
        activeRender = smallRenderer;
        
        capsuleCollider2D.size = new Vector2(1f, 1f);
        capsuleCollider2D.offset = new Vector2(0f, 0f);

        StartCoroutine(ScaleAnimation());
    }

    public void Grow()
    {
        smallRenderer.enabled = false;
        bigRenderer.enabled = true;
        activeRender = bigRenderer;

        capsuleCollider2D.size = new Vector2(1f, 2f);
        capsuleCollider2D.offset = new Vector2(0f, 0.5f);

        StartCoroutine(ScaleAnimation());
    }

    private IEnumerator ScaleAnimation()
    {
        float elapsed = 0f;
        float duration = 0.5f;

        while (elapsed < duration) {
            if (Time.frameCount % 4 == 0) {
                smallRenderer.enabled = !smallRenderer.enabled;
                bigRenderer.enabled = !bigRenderer.enabled;
            }

            elapsed += Time.deltaTime;

            yield return null;
        }

        smallRenderer.enabled = bigRenderer.enabled = false;
        activeRender.enabled = true;

    }

    public void StarPower()
    {
        StartCoroutine(StarPowerAnimation());
    }

    private IEnumerator StarPowerAnimation()
    {
        starPower = true;
        
        float elapsed = 0f, duration = 10f;
        while (elapsed < duration) {
            if (Time.frameCount % 4 == 0) {
                activeRender.spriteRenderer.color = Random.ColorHSV(0f, 1f, 1f, 1f, 1f, 1f);
            }
            elapsed += Time.deltaTime;
            yield return null;
        }

        activeRender.spriteRenderer.color = Color.white;

        starPower = false;
    }
    
}

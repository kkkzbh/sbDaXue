
using UnityEngine;

public static class Extensions
{
    private static readonly LayerMask defaultMask = LayerMask.GetMask("Default");
    
    public static bool Raycast(this Rigidbody2D rigidbody,Vector2 dirction)
    {
        if (rigidbody.isKinematic) {
            return false;
        }

        float radius = 0.25f;
        float distance = 0.375f;
        
        RaycastHit2D hit = Physics2D.CircleCast(rigidbody.position, radius, dirction.normalized, distance,defaultMask);
        return hit.collider != null;
    }

    public static bool DotTest(this Transform transform, Transform other, Vector2 dirction)
    {
        Vector2 vector = (other.position - transform.position).normalized;
        return Vector2.Dot(vector, dirction) > 0.25f;
    }
    
}
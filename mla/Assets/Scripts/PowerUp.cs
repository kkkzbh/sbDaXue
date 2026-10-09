
using System;
using UnityEditor;
using UnityEngine;

public class PowerUp : MonoBehaviour
{
    public enum Type
    {
        Coin,
        UpLifeMushroom,
        MagicMushroom,
        StarMan,
    }

    public Type type;

    private void OnTriggerEnter2D(Collider2D other)
    {
        if (other.CompareTag("Player")) {
            Collected(other.gameObject);
        }
    }

    private void Collected(GameObject Mario)
    {
        switch (type)
        {
            case Type.Coin:
                GameManager.Instance.AddCoin();
                break;
            case Type.UpLifeMushroom:
                GameManager.Instance.AddLife();
                break;
            case Type.MagicMushroom:
                Mario.GetComponent<Player>().Grow();
                break;
            case Type.StarMan:
                Mario.GetComponent<Player>().StarPower();
                break;
        }
        Destroy(gameObject);
    }
    
}


using UnityEngine;
using std;
public class Heart : MonoBehaviour,IDeath
{
    // Start is called before the first frame update

    private SpriteRenderer _sr;
    public Sprite died;

    public GameObject explosionEffect;

    private GameObject _manage;
    private Manage _scManage;

    public AudioClip dieAdc;
    private void Awake()
    {
        _sr = GetComponent<SpriteRenderer>();
        _manage = GameObject.Find("Manage");
        _scManage = _manage.GetComponent<Manage>();
    }

    public void Die()
    {
        Instantiate(explosionEffect, transform.position, Quaternion.identity);
        _sr.sprite = died;
        _scManage.Defeat();
        AudioSource.PlayClipAtPoint(dieAdc,transform.position);
    }
    
}

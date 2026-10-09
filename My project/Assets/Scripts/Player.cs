
using UnityEngine;
using std;
public class Player : MonoBehaviour,IDeath,IBorn
{

    public float moveSpeed = 3.0f;

    //private SpriteRenderer _sr;  // 控制方向

    //public Sprite[] tankSprites; // ↑ → ↓ ←

    private bool _moveH = true;

    private const float TimeInterval = 0.4f;
    private float _timeVal = TimeInterval;

    public GameObject bullet;

    public GameObject explosionEffect;

    private bool _defend = true;
    private float _defendTimeVal = 3.0f;

    public GameObject defendEffect;
    public GameObject bornEffect;

    public GameObject self;

    private GameObject _manage;
    private Manage _scManage;

    public AudioSource moveAdc;
    public AudioClip[] mvAdc;
    public AudioSource fireAdc;
    public enum MoveDirection
    {
        Up,
        Right,
        Down,
        Left,
    }
    
    private void Awake()
    {
        //_sr = GetComponent<SpriteRenderer>();
        _manage = GameObject.Find("Manage");
        _scManage = _manage.GetComponent<Manage>();
        moveAdc.volume = 0.6f;
    }

    // Start is called before the first frame update
    private void Start()
    {
        DefendEffect();
    }
    
    // Update is called once per frame
    private void Update()
    {
        Defend();
        Attack();
    }
    private void FixedUpdate()
    {
        Move();
    }

    private void DefendEffect()
    {
        if (_defend)
        {
            defendEffect.SetActive(true);
        }
    }
    private void Defend()
    {
        if (_defend && (_defendTimeVal -= Time.deltaTime) <= 0)
        {
            _defend = false;
            defendEffect.SetActive(false);
        }
    }

    public void Born()
    {
        var v = Instantiate(self,new Vector3(-2.046f,-7.99f),Quaternion.identity);
        Instantiate(bornEffect, v.transform.position,Quaternion.identity);
    }
    
    public void Die()
    {
        if (!_defend)
        {
            Instantiate(explosionEffect, transform.position, Quaternion.identity);
            _scManage.BornPlayer();
            Destroy(gameObject);
        }
    }

    private void Attack()
    {
        if (_timeVal >= TimeInterval)
        {
            if (Input.GetKey(KeyCode.Space))
            {
                fireAdc.Play();
                var bul = Instantiate(bullet, transform.position, transform.rotation);
                _timeVal = 0;
            }
        }
        else
        {
            _timeVal += Time.deltaTime;
        }
    }
    
    private void Move()
    {
        var h = Input.GetAxisRaw("Horizontal");
        var v = Input.GetAxisRaw("Vertical");
        if (h != 0 && v == 0)
        {
            _moveH = true;
        }
        else if (h == 0 && v != 0)
        {
            _moveH = false;
        }

        if (h != 0 || v != 0)
        {
            
            moveAdc.clip = mvAdc[1];
            if (!moveAdc.isPlaying)
            {
                moveAdc.Play();
            }

            if (h != 0 && v != 0)
            {
                if (_moveH)
                {
                    MoveV();
                }
                else
                {
                    MoveH();
                }
            }
            else if (h != 0)
            {
                MoveH();
            }
            else if (v != 0)
            {
                MoveV();
            }
        }
        else
        {
            moveAdc.clip = mvAdc[0];
            if (!moveAdc.isPlaying)
            {
                moveAdc.Play();
            }
        }
    }

    private void MoveH()
    {
        var moveCof = moveSpeed * Time.fixedDeltaTime;
        var h = Input.GetAxisRaw("Horizontal");
        // if (h > 0)
        // {
        //     _sr.sprite = tankSprites[(int)MoveDirection.Right];
        //     
        // }
        // else if (h < 0)
        // {
        //     _sr.sprite = tankSprites[(int)MoveDirection.Left];
        // }
        transform.rotation = Quaternion.Euler(new Vector3(0, 0, h > 0 ? -90 : 90));
        transform.Translate(h * Vector3.right * moveCof, Space.World);
    }

    private void MoveV()
    {
        var moveCof = moveSpeed * Time.fixedDeltaTime;
        var v = Input.GetAxisRaw("Vertical");
        // if (v > 0)
        // {
        //     _sr.sprite = tankSprites[(int)MoveDirection.Up];
        // }
        // else if (v < 0)
        // {
        //     _sr.sprite = tankSprites[(int)MoveDirection.Down];
        // }
        transform.rotation = Quaternion.Euler(new Vector3(0, 0, v > 0 ? 0 : 180));
        transform.Translate(v * Vector3.up * moveCof, Space.World);
    }
    
}
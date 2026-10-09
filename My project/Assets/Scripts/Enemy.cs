
using System.Collections.Generic;
using UnityEngine;
using std;
using Random = UnityEngine.Random;

public class Enemy : MonoBehaviour,IDeath,IBorn
{

    public float moveSpeed = 3.0f;

    private const float AtkTimeCeil = 3.5f;
    private const float AtkTimeFloor = 1.2f;
    private float _atkTimeInterval;
    private float _atkTimeVal;

    private const float MoveTimeCeil = 2.2f;
    private const float MoveTimeFloor = 1.33f;
    private float _rotationTimeInterval;
    private float _rotationTimeVal;
    private Vector3 _moveDir;
    private Vector3 _rotationDir;
    
    public GameObject bullet;

    public GameObject explosionEffect;
    public GameObject bornEffect;

    public GameObject self;

    private GameObject _manage;
    private Manage _scManage;

    public List<Vector3> bornPos = new List<Vector3>()
    {
        new Vector3(-9,7),
        new Vector3(0,7),
        new Vector3(8,6),
    };
    public enum Kind
    {
        Enemy,
        SEnemy,
    }

    public Kind kind;
    public enum MoveDirection
    {
        Up,
        Right,
        Down,
        Left,
    }

    private void Awake()
    {
        _manage = GameObject.Find("Manage");
        _scManage = _manage.GetComponent<Manage>();
    }

    // Start is called before the first frame update
    private void Start()
    {
        _atkTimeInterval = _atkTimeVal = Random.Range(AtkTimeFloor, AtkTimeCeil);
        _rotationTimeInterval = _rotationTimeVal = Random.Range(MoveTimeFloor, MoveTimeCeil);
    }
    
    // Update is called once per frame
    private void Update()
    {
        Attack();
    }
    private void FixedUpdate()
    {
        Rotation();
        Move();
    }
    
    public void Born()
    {
        var v = Instantiate(self,bornPos[Random.Range(0,bornPos.Count)],Quaternion.identity);
        Instantiate(bornEffect, v.transform.position, Quaternion.identity);
    }
    public void Die()
    {
        Instantiate(explosionEffect, transform.position,Quaternion.identity);
        _scManage.BornEnemy(kind);
        Destroy(gameObject);
    }

    private void Attack()
    {
        if(_atkTimeVal >= _atkTimeInterval)
        {
            var bul = Instantiate(bullet, transform.position, transform.rotation);
            _atkTimeVal = 0;
            _atkTimeInterval = Random.Range(AtkTimeFloor, AtkTimeCeil);
        }
        else
        {
            _atkTimeVal += Time.deltaTime;
        }
    }
    
    private void Move()
    {
        transform.Translate(moveSpeed * _moveDir * Time.fixedDeltaTime,Space.World);
        transform.rotation = Quaternion.Euler(_rotationDir);
    }

    private void Rotation()
    {
        if (_rotationTimeVal >= _rotationTimeInterval)
        {
            _rotationTimeVal = 0;
            _rotationTimeInterval = Random.Range(MoveTimeFloor, MoveTimeCeil);
            int ran = Random.Range(0, 10);
            if (_moveDir == Vector3.up || _moveDir == Vector3.down)
            {
                switch (ran)
                {
                    case 0:
                        _moveDir = Vector3.up;
                        _rotationDir = Vector3.zero;
                        break;
                    case 1:
                    case 2:
                    case 3:
                        _moveDir = Vector3.left;
                        _rotationDir = new Vector3(0, 0, 90);
                        break;
                    case 4:
                    case 5:
                    case 6:
                    case 7:
                        _moveDir = Vector3.right;
                        _rotationDir = new Vector3(0, 0, -90);
                        break;
                    case 8:
                    case 9:
                        _moveDir = Vector3.down;
                        _rotationDir = new Vector3(0, 0, 180);
                        break;
                }
            }
            else
            {
                switch (ran)
                {
                    case 0:
                        _moveDir = Vector3.up;
                        _rotationDir = Vector3.zero;
                        break;
                    case 1:
                    case 2:
                    case 3:
                        _moveDir = Vector3.left;
                        _rotationDir = new Vector3(0, 0, 90);
                        break;
                    case 4:
                    case 5:
                    case 6:
                        _moveDir = Vector3.right;
                        _rotationDir = new Vector3(0, 0, -90);
                        break;
                    case 7:
                    case 8:
                    case 9:
                        _moveDir = Vector3.down;
                        _rotationDir = new Vector3(0, 0, 180);
                        break;
                }
            }
        }
        else
        {
            _rotationTimeVal += Time.deltaTime;
        }
    }

    private void OnCollisionStay2D(Collision2D other)
    {
        if (other.gameObject.CompareTag("Enemy") || other.gameObject.CompareTag("Barrier") || other.gameObject.CompareTag("Barrier"))
        {
            _rotationTimeVal = _rotationTimeInterval;
        }
    }
}
"""
测试用例 - 刺杀博弈核心逻辑
"""

import pytest
import sys
import os

# 添加父目录到路径
sys.path.insert(0, os.path.dirname(os.path.dirname(os.path.abspath(__file__))))

from bayesian_game_ import AssassinationGame, game_manager


class TestBeliefParsing:
    """测试信念值解析"""
    
    def test_parse_fraction(self):
        """测试分数解析"""
        game = AssassinationGame(seed=42)
        
        assert abs(game.parse_belief("2/3") - 2/3) < 1e-9
        assert abs(game.parse_belief("1/2") - 0.5) < 1e-9
        assert abs(game.parse_belief("0/1") - 0) < 1e-9
        assert abs(game.parse_belief("1/1") - 1) < 1e-9
    
    def test_parse_decimal(self):
        """测试小数解析"""
        game = AssassinationGame(seed=42)
        
        assert abs(game.parse_belief("0.5") - 0.5) < 1e-9
        assert abs(game.parse_belief("0.667") - 0.667) < 1e-9
        assert abs(game.parse_belief("0") - 0) < 1e-9
        assert abs(game.parse_belief("1") - 1) < 1e-9
    
    def test_parse_float(self):
        """测试浮点数输入"""
        game = AssassinationGame(seed=42)
        
        assert abs(game.parse_belief(0.5) - 0.5) < 1e-9
        assert abs(game.parse_belief(0) - 0) < 1e-9
        assert abs(game.parse_belief(1) - 1) < 1e-9


class TestBeliefValidation:
    """测试信念值验证"""
    
    def test_valid_beliefs(self):
        """测试有效信念值"""
        game = AssassinationGame(seed=42)
        game.set_killer_beliefs("2/3", "0")
        
        assert game.killer_beliefs is not None
        assert abs(game.killer_beliefs['guard']['gun'] - 2/3) < 1e-9
        assert abs(game.killer_beliefs['hide']['gun'] - 0) < 1e-9
    
    def test_endpoint_beliefs(self):
        """测试端点值 0 和 1"""
        game = AssassinationGame(seed=42)
        
        game.set_killer_beliefs("0", "1")
        assert game.killer_beliefs['guard']['gun'] == 0
        assert game.killer_beliefs['hide']['gun'] == 1
        
        game.set_killer_beliefs("1", "0")
        assert game.killer_beliefs['guard']['gun'] == 1
        assert game.killer_beliefs['hide']['gun'] == 0
    
    def test_invalid_beliefs(self):
        """测试无效信念值"""
        game = AssassinationGame(seed=42)
        
        with pytest.raises(ValueError):
            game.set_killer_beliefs("1.5", "0")  # 超出范围
        
        with pytest.raises(ValueError):
            game.set_killer_beliefs("-0.1", "0")  # 负数


class TestSeedReproducibility:
    """测试种子可复现性"""
    
    def test_same_seed_same_result(self):
        """相同种子应产生相同结果"""
        game1 = AssassinationGame(seed=12345)
        game2 = AssassinationGame(seed=12345)
        
        assert game1.p_gun == game2.p_gun
        assert game1.p_empty == game2.p_empty
    
    def test_different_seed_different_result(self):
        """不同种子应产生不同结果（大概率）"""
        game1 = AssassinationGame(seed=12345)
        game2 = AssassinationGame(seed=54321)
        
        # 不同种子大概率产生不同结果
        assert game1.p_gun != game2.p_gun
    
    def test_auto_seed_generation(self):
        """测试自动种子生成"""
        game = AssassinationGame()
        assert game.seed is not None
        assert 0 <= game.seed < 2**32

    def test_fixed_prior_gun(self):
        """测试固定先验概率"""
        game = AssassinationGame(seed=42, prior_gun=0.5)
        assert game.p_gun == 0.5
        assert game.p_empty == 0.5

        with pytest.raises(ValueError):
            AssassinationGame(seed=42, prior_gun=1.5)


class TestKillerBestResponse:
    """测试杀手最优反应计算"""
    
    def test_pure_strategy_kill(self):
        """测试纯策略 - 刺杀更优"""
        game = AssassinationGame(seed=42)
        # 设置收益矩阵使刺杀有优势
        game.payoff = {
            'gun': {
                'guard': {'kill': (0, 10), 'leave': (0, 0)},
                'hide': {'kill': (0, 10), 'leave': (0, 0)}
            },
            'empty': {
                'guard': {'kill': (0, 10), 'leave': (0, 0)},
                'hide': {'kill': (0, 10), 'leave': (0, 0)}
            }
        }
        game.set_killer_beliefs("0.5", "0.5")
        
        response = game.compute_killer_best_response('guard')
        assert response['type'] == 'pure'
        assert response['action'] == 'kill'
    
    def test_pure_strategy_leave(self):
        """测试纯策略 - 离开更优"""
        game = AssassinationGame(seed=42)
        # 设置收益矩阵使离开有优势
        game.payoff = {
            'gun': {
                'guard': {'kill': (0, -10), 'leave': (0, 5)},
                'hide': {'kill': (0, -10), 'leave': (0, 5)}
            },
            'empty': {
                'guard': {'kill': (0, -10), 'leave': (0, 5)},
                'hide': {'kill': (0, -10), 'leave': (0, 5)}
            }
        }
        game.set_killer_beliefs("0.5", "0.5")
        
        response = game.compute_killer_best_response('guard')
        assert response['type'] == 'pure'
        assert response['action'] == 'leave'
    
    def test_mixed_strategy(self):
        """测试混合策略 - 期望收益相等"""
        game = AssassinationGame(seed=42)
        # 设置收益矩阵使期望收益相等
        game.payoff = {
            'gun': {
                'guard': {'kill': (0, 5), 'leave': (0, 5)},
                'hide': {'kill': (0, 5), 'leave': (0, 5)}
            },
            'empty': {
                'guard': {'kill': (0, 5), 'leave': (0, 5)},
                'hide': {'kill': (0, 5), 'leave': (0, 5)}
            }
        }
        game.set_killer_beliefs("0.5", "0.5")
        
        response = game.compute_killer_best_response('guard')
        assert response['type'] == 'mixed'
        assert response['p_kill'] == 0.5


class TestBayesianVerification:
    """测试贝叶斯验证"""
    
    def test_consistent_beliefs(self):
        """测试一致信念：两种类型都选择把守"""
        game = AssassinationGame(seed=42)
        game.p_gun = 0.5
        game.p_empty = 0.5
        game.mike_strategy = {
            'gun': {'guard': 1.0, 'hide': 0.0},
            'empty': {'guard': 1.0, 'hide': 0.0}
        }
        game.killer_beliefs = {
            'guard': {'gun': 0.5, 'empty': 0.5},
            'hide': {'gun': 0.1234, 'empty': 0.8766}  # 路径外信念不做验证
        }
        
        result = game.verify_beliefs()
        assert result['pbe_established'] is True
        assert result['details']['guard']['on_path'] is True
        assert result['details']['guard']['match'] is True
        assert abs(result['details']['guard']['posterior_gun'] - 0.5) < 1e-9
        assert result['details']['hide']['on_path'] is False

    def test_inconsistent_beliefs(self):
        """测试不一致信念：把守在路径上但信念偏离"""
        game = AssassinationGame(seed=42)
        game.p_gun = 0.5
        game.p_empty = 0.5
        game.mike_strategy = {
            'gun': {'guard': 1.0, 'hide': 0.0},
            'empty': {'guard': 1.0, 'hide': 0.0}
        }
        game.killer_beliefs = {
            'guard': {'gun': 0.6, 'empty': 0.4},  # 应为0.5
            'hide': {'gun': 0.0, 'empty': 1.0}
        }
        
        result = game.verify_beliefs()
        assert result['pbe_established'] is False
        assert result['details']['guard']['on_path'] is True
        assert result['details']['guard']['match'] is False

    def test_separating_strategy_beliefs(self):
        """测试分离策略下的后验：gun->guard, empty->hide"""
        game = AssassinationGame(seed=42)
        game.p_gun = 0.5
        game.p_empty = 0.5
        game.mike_strategy = {
            'gun': {'guard': 1.0, 'hide': 0.0},
            'empty': {'guard': 0.0, 'hide': 1.0}
        }
        game.killer_beliefs = {
            'guard': {'gun': 1.0, 'empty': 0.0},
            'hide': {'gun': 0.0, 'empty': 1.0}
        }
        
        result = game.verify_beliefs()
        assert result['pbe_established'] is True
        assert result['details']['guard']['on_path'] is True
        assert result['details']['guard']['match'] is True
        assert abs(result['details']['guard']['posterior_gun'] - 1.0) < 1e-9
        assert abs(result['details']['guard']['p_action'] - 0.5) < 1e-9
        assert result['details']['hide']['on_path'] is True
        assert result['details']['hide']['match'] is True
        assert abs(result['details']['hide']['posterior_gun'] - 0.0) < 1e-9
        assert abs(result['details']['hide']['p_action'] - 0.5) < 1e-9
    
    def test_zero_probability_action(self):
        """测试概率为 0 的行动"""
        game = AssassinationGame(seed=42)
        game.p_gun = 0.5
        game.p_empty = 0.5
        
        # 设置使迈克总是选择把守的收益矩阵
        game.payoff = {
            'gun': {
                'guard': {'kill': (100, -10), 'leave': (50, 0)},
                'hide': {'kill': (-100, 10), 'leave': (-50, 0)}
            },
            'empty': {
                'guard': {'kill': (100, -10), 'leave': (50, 0)},
                'hide': {'kill': (-100, 10), 'leave': (-50, 0)}
            }
        }
        
        game.set_killer_beliefs("0.5", "0.5")
        game.compute_equilibrium()
        
        result = game.verify_beliefs()
        # 躲避应该不在路径上
        assert result['details']['hide']['on_path'] is False
        assert '跳过验证' in result['details']['hide']['message']

    def test_semi_separating_pbe(self):
        """测试半分离预设：gun 纯策略、empty 混合，且信念匹配后验"""
        game = AssassinationGame(seed=42, prior_gun=0.5)
        game.set_payoff_matrix({
            'gun': {
                'guard': {'kill': (2, -2), 'leave': (5, 0)},
                'hide': {'kill': (0, 1), 'leave': (1, 0)}
            },
            'empty': {
                'guard': {'kill': (0, 2), 'leave': (2, 0)},
                'hide': {'kill': (2, 2), 'leave': (2, 0)}
            }
        })
        game.set_killer_beliefs("2/3", "0")
        game.compute_equilibrium()

        assert game.mike_strategy['gun']['guard'] == 1.0
        assert game.mike_strategy['gun']['hide'] == 0.0
        assert game.mike_strategy['empty']['type'] == 'mixed'
        assert game.killer_response['guard']['type'] == 'pure'
        assert game.killer_response['guard']['action'] == 'leave'
        assert game.killer_response['hide']['type'] == 'pure'
        assert game.killer_response['hide']['action'] == 'kill'

        result = game.verify_beliefs()
        assert result['pbe_established'] is True


class TestPresetRegression:
    """回归测试：确保五种预设互不互相破坏"""

    def test_preset_separating_pbe(self):
        game = AssassinationGame(seed=42, prior_gun=0.5)
        game.set_payoff_matrix({
            'gun': {
                'guard': {'kill': (1, -10), 'leave': (4, 0)},
                'hide': {'kill': (0, 2), 'leave': (1, 0)}
            },
            'empty': {
                'guard': {'kill': (-5, 2), 'leave': (-2, 0)},
                'hide': {'kill': (-1, 2), 'leave': (0, 0)}
            }
        })
        game.set_killer_beliefs("1", "0")
        game.compute_equilibrium()
        result = game.verify_beliefs()
        assert result['pbe_established'] is True

    def test_preset_pooling_base_success_when_belief_equals_prior(self):
        game = AssassinationGame(seed=42, prior_gun=0.5)
        game.set_payoff_matrix({
            'gun': {
                'guard': {'kill': (2, -2), 'leave': (5, 0)},
                'hide': {'kill': (0, 1), 'leave': (1, 0)}
            },
            'empty': {
                'guard': {'kill': (0, 1), 'leave': (3, 0)},
                'hide': {'kill': (-2, 2), 'leave': (-1, 0)}
            }
        })
        game.set_killer_beliefs("0.5", "0.5")
        game.compute_equilibrium()

        assert game.mike_strategy['gun']['guard'] == 1.0
        assert game.mike_strategy['empty']['guard'] == 1.0

        result = game.verify_beliefs()
        assert result['pbe_established'] is True

    def test_preset_pooling_bias_should_fail(self):
        game = AssassinationGame(seed=42, prior_gun=0.5)
        game.set_payoff_matrix({
            'gun': {
                'guard': {'kill': (2, -2), 'leave': (5, 0)},
                'hide': {'kill': (0, 1), 'leave': (1, 0)}
            },
            'empty': {
                'guard': {'kill': (0, 1), 'leave': (3, 0)},
                'hide': {'kill': (-2, 2), 'leave': (-1, 0)}
            }
        })
        game.set_killer_beliefs("0.8", "0.2")
        game.compute_equilibrium()
        result = game.verify_beliefs()
        assert result['pbe_established'] is False

    def test_preset_belief_mismatch_should_fail(self):
        game = AssassinationGame(seed=42, prior_gun=0.5)
        # 使用默认收益矩阵
        game.set_killer_beliefs("0.9", "0.1")
        game.compute_equilibrium()
        result = game.verify_beliefs()
        assert result['pbe_established'] is False


class TestGameFlow:
    """测试游戏流程"""
    
    def test_full_game_flow(self):
        """测试完整游戏流程"""
        game = AssassinationGame(seed=42)
        
        # 1. 设置收益矩阵（使用默认）
        assert game.payoff is not None
        
        # 2. 设置信念
        game.set_killer_beliefs("2/3", "1/3")
        assert game.killer_beliefs is not None
        
        # 3. 计算均衡
        game.compute_equilibrium()
        assert game.mike_strategy is not None
        assert game.killer_response is not None
        
        # 4. 迈克行动
        action, cond_probs = game.execute_mike_action()
        assert action in ['guard', 'hide']
        assert game.actual_state in ['gun', 'empty']
        
        # 5. 杀手行动
        result = game.submit_killer_action('kill')
        assert 'mike_payoff' in result
        assert 'killer_payoff' in result
        assert 'winner' in result
        
        # 6. 验证信念
        verification = game.verify_beliefs()
        assert 'pbe_established' in verification
        assert 'details' in verification
    
    def test_game_reset(self):
        """测试游戏重置"""
        game = AssassinationGame(seed=42)
        game.set_killer_beliefs("0.5", "0.5")
        game.compute_equilibrium()
        game.execute_mike_action()
        game.submit_killer_action('kill')
        
        old_p_gun = game.p_gun
        game.reset(new_seed=12345)
        
        # 验证重置后的状态
        assert game.p_gun == old_p_gun
        assert game.mike_action is None
        assert game.killer_action is None
        assert game.game_result is None
        # 信念应保留
        assert game.killer_beliefs is not None

        game.reset(new_seed=54321, reset_prior=True)
        assert game.p_gun != old_p_gun


class TestGameManager:
    """测试游戏管理器"""
    
    def test_create_game(self):
        """测试创建游戏"""
        game_id = game_manager.create_game()
        assert game_id is not None
        
        game = game_manager.get_game(game_id)
        assert isinstance(game, AssassinationGame)
    
    def test_get_nonexistent_game(self):
        """测试获取不存在的游戏"""
        with pytest.raises(KeyError):
            game_manager.get_game("nonexistent_game")
    
    def test_delete_game(self):
        """测试删除游戏"""
        game_id = game_manager.create_game()
        game_manager.delete_game(game_id)
        
        with pytest.raises(KeyError):
            game_manager.get_game(game_id)


class TestExpectedPayoffCalculation:
    """测试期望收益计算"""
    
    def test_mike_expected_payoff_pure(self):
        """测试迈克期望收益 - 杀手纯策略"""
        game = AssassinationGame(seed=42)
        game.payoff = {
            'gun': {
                'guard': {'kill': (5, 0), 'leave': (10, 0)},
                'hide': {'kill': (2, 0), 'leave': (8, 0)}
            },
            'empty': {
                'guard': {'kill': (-5, 10), 'leave': (3, 0)},
                'hide': {'kill': (-8, 15), 'leave': (1, 0)}
            }
        }
        game.set_killer_beliefs("0.9", "0.1")
        game.compute_equilibrium()
        
        # 验证期望收益已计算
        assert 'E_guard' in game.mike_strategy['gun']
        assert 'E_hide' in game.mike_strategy['gun']
    
    def test_mike_expected_payoff_mixed(self):
        """测试迈克期望收益 - 杀手混合策略"""
        game = AssassinationGame(seed=42)
        # 使杀手无差异
        game.payoff = {
            'gun': {
                'guard': {'kill': (5, 5), 'leave': (10, 5)},
                'hide': {'kill': (2, 5), 'leave': (8, 5)}
            },
            'empty': {
                'guard': {'kill': (-5, 5), 'leave': (3, 5)},
                'hide': {'kill': (-8, 5), 'leave': (1, 5)}
            }
        }
        game.set_killer_beliefs("0.5", "0.5")
        game.compute_equilibrium()
        
        # 杀手应该是混合策略
        assert game.killer_response['guard']['type'] == 'mixed'


if __name__ == "__main__":
    pytest.main([__file__, "-v"])

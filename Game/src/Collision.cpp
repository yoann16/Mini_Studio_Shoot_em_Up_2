//#include "Collision.h"
//
//#include "IGameObject.h"
//
//bool Collision(AABB A, AABB B)
//{
//	if (A.Amax.x <= B.Amin.x || A.Amin.x >= B.Amax.x || A.Amax.y <= B.Amin.y || A.Amin.y >= B.Amax.y)
//		return false;
//	else
//		return true;
//}
//
//void Colision::HandleCollision(KT::Vector<IComponent*> objects)
//{
//	for (std::make_signed_t<size_t> i = objects.Size() - 1; i >= 0; --i)
//	{
//		for (std::make_signed_t<size_t> y = i - 1; y >= 0; --y)
//		{
//				if (auto* obj1 = getObj<IGameObject*>(objects[i]))
//				{
//					if (auto obj2 = getObj<IGameObject*>(objects[y]))
//					{
//						if (Collision(obj1->GetBoundingBox(), obj2->GetBoundingBox()))
//						{
//							if (Compose(objects[i], objects[y]))
//								continue;
//							obj1->HandleCollision(obj2);
//							obj2->HandleCollision(obj1);
//						}
//					}
//				}
//		}
//	}
//
//
//	destroy(objects);
//}
//
//
//bool Colision::Compose(IComponent* lhs, IComponent* rhs)
//{
//	if (lhs == rhs)
//		return true;
//	if (lhs->GetComponentType() == Component::IComposite)
//	{
//		auto lhsCompose = static_cast<IComposite*>(lhs)->getFullTree();
//		for (auto tree : lhsCompose)
//		{
//			if (tree == rhs)
//				return true;
//		}
//	}
//	if (rhs->GetComponentType() == Component::IComposite)
//	{
//		auto lhsCompose = static_cast<IComposite*>(rhs)->getFullTree();
//		for (auto tree : lhsCompose)
//		{
//			if (tree == lhs)
//				return true;
//		}
//	}
//	return false;
//}
//
//void Colision::destroy(KT::Vector<IComponent*> objects)
//{
//	for (std::make_signed_t<size_t> i = objects.Size() - 1; i >= 0; --i)
//	{
//		if (auto obj = getObj<IGameObject*>(objects[i]))
//		{
//			if (obj->NeedDestroy())
//				delete obj;
//		}
//	}
//
//}